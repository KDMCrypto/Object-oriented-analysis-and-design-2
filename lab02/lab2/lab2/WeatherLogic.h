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

	// класс для представления общих данных о погоде
	public ref class WeatherData {
	public:
		String^ city;
		bool fromCache = false;
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
		virtual WeatherData^ getWeather(String^ city) abstract; 
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

				//System::Windows::Forms::MessageBox::Show("Ошибка парсинга: " + response);

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
		virtual WeatherData^ getWeather(String^ city) override {
			return FetchDataFromApi(city);
		}


	private:
		WeatherData^ FetchDataFromApi(String^ city) {
			try {
				String^ url = "https://api.open-meteo.com/v1/forecast?" + GetCoords(city) +
					"&daily=temperature_2m_max,temperature_2m_min,weather_code,windspeed_10m_max,relative_humidity_2m_max" +
					"&timezone=auto";

				String^ json = httpClient->GetStringAsync(url)->Result;

				WeatherData^ data = gcnew WeatherData();
				data->city = city;
				data->fromCache = false;

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

						data->days->Add(day);
					}
				}
				
				return data;
			}
			catch (Exception^ ex) {
				System::Windows::Forms::MessageBox::Show("Ошибка парсинга: " + ex->Message);
				return nullptr;
			}
		}

		array<String^>^ GetJsonArray(String^ json, String^ key) {
			String^ searchKey = "\"" + key + "\":[";
			int start = json->IndexOf(searchKey);
			if (start == -1) return nullptr;

			start += searchKey->Length;
			int end = json->IndexOf("]", start);
			String^ content = json->Substring(start, end - start);

			return content->Replace("\"", "")->Split(',');
		}
	};


	public ref class ProxyWeather : public WeatherService {
	private:
		RealWeatherService^ realWeather;
		Dictionary<String^, CacheEntry^>^ cache;

	public:
		ProxyWeather() {
			realWeather = gcnew RealWeatherService();
			cache = gcnew Dictionary<String^, CacheEntry^>();
		}

		virtual WeatherData^ getWeather(String^ city) override {
			// логика кэша
			if (cache->ContainsKey(city)) {
				if ((DateTime::Now - cache[city]->time).TotalMinutes < 5) {

					WeatherData^ cachedData = cache[city]->data; // выдача из кэша
					cachedData->fromCache = true;
					return cachedData;
				}
			}
			WeatherData^ freshData = realWeather->getWeather(city); // Идем в сеть

			// Сохраняем в кэш при получении из сети
			if (freshData != nullptr) {
				cache[city] = gcnew CacheEntry(freshData);
			}

			return freshData;
		}

	};

}

