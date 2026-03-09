#pragma once

namespace lab2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Net::Http;

	// класс для представления данных одного дня
	public ref class DailyForecast {
	public:
		String^ date;
		double tempMax;
		double tempMin;
		int weatherCode;
		double windSpeed;
		int humidity;
	};

	// класс для представления данных 
	public ref class WeatherData {
	public:
		String^ city;
		// Список для хранения 7 дней прогноза
		System::Collections::Generic::List<DailyForecast^>^ days = gcnew System::Collections::Generic::List<DailyForecast^>();
	};

	// класс кэша
	public ref class CacheEntry {
	public:
		WeatherData^ data;
		DateTime time;
		CacheEntry(WeatherData^ d) {
			data = d;
			time = DateTime::Now;
		}
	};

	// абстрактный класс для погоды
	public ref class WeatherService abstract {
	public:
		// Делегат для уведомления формы об ответе
		delegate void WeatherCallback(WeatherData^ data, bool fromCache);
		event WeatherCallback^ OnDataReady;

		virtual void getWeather(String^ city) abstract; 

	protected:
		void Notify(WeatherData^ data, bool fromCache) {
			OnDataReady(data, fromCache);
		}
	};


	// реальный запрос к API
	public ref class RealWeatherService : public WeatherService {
	private:
		HttpClient^ httpClient = gcnew HttpClient();

		// Конвертируем название в координаты
		String^ GetCoords(String^ city) {
			try {
				System::Net::Http::HttpClient^ client = gcnew System::Net::Http::HttpClient();
				String^ url = "https://geocoding-api.open-meteo.com/v1/search?name=" + city + "&count=1&language=ru&format=json";
				String^ response = client->GetStringAsync(url)->Result;

				System::Windows::Forms::MessageBox::Show("Ошибка парсинга: " + response);

				if (!response->Contains("\"results\":")) {
					MessageBox::Show("Город '" + city + "' не найден. Проверьте правильность написания.", "Ошибка поиска");
					return "error";
				}

				int latIndex = response->IndexOf("\"latitude\":") + 11;
				int lonIndex = response->IndexOf("\"longitude\":") + 12;

				String^ lat = response->Substring(latIndex, response->IndexOf(",", latIndex) - latIndex);
				String^ lon = response->Substring(lonIndex, response->IndexOf(",", lonIndex) - lonIndex);

				return "latitude=" + lat + "&longitude=" + lon;

			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка сети или сервиса геокодинга.", "Внимание");
				return "error";
			}
		}

	public:
		virtual void getWeather(String^ city) override {
			FetchDataFromApi(city, false);
		}


	private:
		void FetchDataFromApi(String^ city, bool detailed) {
			try {
				String^ url = "https://api.open-meteo.com/v1/forecast?" + GetCoords(city) +
					"&daily=temperature_2m_max,temperature_2m_min,weather_code,windspeed_10m_max,relative_humidity_2m_max" +
					"&timezone=auto";

				String^ json = httpClient->GetStringAsync(url)->Result;

				WeatherData^ data = gcnew WeatherData();
				data->city = city;

				// Извлекаем массивы данных
				array<String^>^ dates = GetJsonArray(json, "time");
				array<String^>^ tempsMax = GetJsonArray(json, "temperature_2m_max");
				array<String^>^ tempsMin = GetJsonArray(json, "temperature_2m_min");
				array<String^>^ codes = GetJsonArray(json, "weather_code");
				array<String^>^ winds = GetJsonArray(json, "windspeed_10m_max");
				array<String^>^ hums = GetJsonArray(json, "relative_humidity_2m_max");

				// Проверяем, что данные успешно получены
				if (dates != nullptr && tempsMax != nullptr) {
					for (int i = 0; i < dates->Length; i++) {
						DailyForecast^ day = gcnew DailyForecast();

						day->date = dates[i];
						day->tempMax = Double::Parse(tempsMax[i], System::Globalization::CultureInfo::InvariantCulture);
						day->tempMin = Double::Parse(tempsMin[i], System::Globalization::CultureInfo::InvariantCulture);
						day->weatherCode = Int32::Parse(codes[i]);
						day->windSpeed = Double::Parse(winds[i], System::Globalization::CultureInfo::InvariantCulture);
						day->humidity = Int32::Parse(hums[i]);

						data->days->Add(day); // Добавляем в общий список
					}
				}

				Notify(data, false);
			}
			catch (Exception^ ex) {
				System::Windows::Forms::MessageBox::Show("Ошибка парсинга: " + ex->Message);
			}
		}

		array<String^>^ GetJsonArray(String^ json, String^ key) {
			String^ searchKey = "\"" + key + "\":[";
			int start = json->IndexOf(searchKey);
			if (start == -1) return nullptr;

			start += searchKey->Length;
			int end = json->IndexOf("]", start);
			String^ content = json->Substring(start, end - start);

			// Разделяем строку по запятым и убираем кавычки, если это массив строк (как даты)
			return content->Replace("\"", "")->Split(',');
		}
	};


	public ref class ProxyWeather : public WeatherService {
	private:
		RealWeatherService^ realWeather;
		Dictionary<String^, CacheEntry^>^ cache;

	public:
		ProxyWeather(bool vipStatus) {
			this->realWeather = gcnew RealWeatherService();
		}

		ProxyWeather() {
			realWeather = gcnew RealWeatherService();
			cache = gcnew Dictionary<String^, CacheEntry^>();

			// Перехватываем ответ от реального сервиса, чтобы сохранить в кэш
			realWeather->OnDataReady += gcnew WeatherCallback(this, &ProxyWeather::OnInternalDataReady);
		}

		virtual void getWeather(String^ city) override {
			// ЛОГИКА КЭШИРОВАНИЯ
			if (cache->ContainsKey(city)) {
				if ((DateTime::Now - cache[city]->time).TotalMinutes < 5) {
					Notify(cache[city]->data, true); // Выдача из кэша
					return;
				}
			}
			realWeather->getWeather(city); // Идем в сеть
		}

	private:
		void OnInternalDataReady(WeatherData^ data, bool fromCache) {
			// Сохраняем в кэш при получении из сети
			cache[data->city] = gcnew CacheEntry(data);
			Notify(data, fromCache);
		}
	};

}

