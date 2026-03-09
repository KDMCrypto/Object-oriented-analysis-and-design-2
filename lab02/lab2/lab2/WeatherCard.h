#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace lab2 {

	/// <summary>
	/// Сводка для WeatherCard
	/// </summary>
	public ref class WeatherCard : public System::Windows::Forms::UserControl
	{
	public:
		WeatherCard(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

		System::Drawing::Image^ GetIcon(int code) {
			// Получаем доступ к ресурсам текущей формы/карточки
			System::ComponentModel::ComponentResourceManager^ resources =
				gcnew System::ComponentModel::ComponentResourceManager(WeatherCard::typeid);

			// Логика выбора ресурса по коду (имена в L"..." должны совпадать с именами в твоем resx)
			switch (code) {
			case 0:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"sun")));;
			case 1: case 2: case 3:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cloudy")));
			case 45: case 48:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fog")));
			case 51: case 53: case 55:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"drizzle")));
			case 61: case 63: case 65:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"rain")));
			case 66: case 67:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ice")));
			case 71: case 73: case 75:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"snow")));
			case 95: case 96: case 99:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"storm")));
			default:
				return (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"default")));
			}
		}

		String^ GetDescription(int code) {
			switch (code) {
			case 0: return "Ясно";
			case 1: case 2: case 3: return "Облачно";
			case 45: case 48: return "Туман";
			case 51: case 53: case 55: return "Морось";
			case 61: case 63: case 65: return "Дождь";
			case 66: case 67: return "Гололед";
			case 71: case 73: case 75: return "Снег";
			case 95: case 96: case 99: return "Гроза";
			default: return "Осадки";
			}
		}

		void SetData(String^ date, double tMax, double tMin, double wind, int hum, int code) {
			// Парсим дату, чтобы красиво выделить день недели
			this->labelDate->Text = date;
			this->labelWeatherCode->Text = GetDescription(code);
			this->labelTempMax->Text = (tMax > 0 ? "+" : "") + tMax.ToString() + "°C";
			this->labelTempMin->Text = (tMin > 0 ? "+" : "") + tMin.ToString() + "°C";
			this->labelWind->Text = wind.ToString() + " м/с";
			this->labelHumidity->Text = hum.ToString() + "%";

			this->pictureBoxCard->Image = GetIcon(code);
			//this->pictureBoxCard->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~WeatherCard()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelDate;
	private: System::Windows::Forms::PictureBox^ pictureBoxCard;
	protected:

	private: System::Windows::Forms::Label^ labelTempMax;
	private: System::Windows::Forms::Label^ labelTempMin;
	private: System::Windows::Forms::Label^ labelWind;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ labelHumidity;
	private: System::Windows::Forms::Label^ labelWeatherCode;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelDate = (gcnew System::Windows::Forms::Label());
			this->pictureBoxCard = (gcnew System::Windows::Forms::PictureBox());
			this->labelTempMax = (gcnew System::Windows::Forms::Label());
			this->labelTempMin = (gcnew System::Windows::Forms::Label());
			this->labelWind = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->labelHumidity = (gcnew System::Windows::Forms::Label());
			this->labelWeatherCode = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCard))->BeginInit();
			this->SuspendLayout();
			// 
			// labelDate
			// 
			this->labelDate->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelDate->Location = System::Drawing::Point(49, 9);
			this->labelDate->Name = L"labelDate";
			this->labelDate->Size = System::Drawing::Size(114, 25);
			this->labelDate->TabIndex = 0;
			this->labelDate->Text = L"label1";
			this->labelDate->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBoxCard
			// 
			this->pictureBoxCard->BackColor = System::Drawing::Color::Transparent;
			this->pictureBoxCard->Location = System::Drawing::Point(62, 96);
			this->pictureBoxCard->Name = L"pictureBoxCard";
			this->pictureBoxCard->Size = System::Drawing::Size(100, 100);
			this->pictureBoxCard->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBoxCard->TabIndex = 1;
			this->pictureBoxCard->TabStop = false;
			// 
			// labelTempMax
			// 
			this->labelTempMax->AutoSize = true;
			this->labelTempMax->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTempMax->Location = System::Drawing::Point(82, 247);
			this->labelTempMax->Name = L"labelTempMax";
			this->labelTempMax->Size = System::Drawing::Size(59, 25);
			this->labelTempMax->TabIndex = 2;
			this->labelTempMax->Text = L"label1";
			// 
			// labelTempMin
			// 
			this->labelTempMin->AutoSize = true;
			this->labelTempMin->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTempMin->Location = System::Drawing::Point(82, 292);
			this->labelTempMin->Name = L"labelTempMin";
			this->labelTempMin->Size = System::Drawing::Size(62, 25);
			this->labelTempMin->TabIndex = 3;
			this->labelTempMin->Text = L"label2";
			// 
			// labelWind
			// 
			this->labelWind->AutoSize = true;
			this->labelWind->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelWind->Location = System::Drawing::Point(82, 397);
			this->labelWind->Name = L"labelWind";
			this->labelWind->Size = System::Drawing::Size(59, 25);
			this->labelWind->TabIndex = 4;
			this->labelWind->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(63, 350);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(99, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Ветер, м/с";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(4, 213);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(219, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Температура воздуха, °C";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(45, 442);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(128, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Влажность, %";
			// 
			// labelHumidity
			// 
			this->labelHumidity->AutoSize = true;
			this->labelHumidity->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHumidity->Location = System::Drawing::Point(82, 485);
			this->labelHumidity->Name = L"labelHumidity";
			this->labelHumidity->Size = System::Drawing::Size(62, 25);
			this->labelHumidity->TabIndex = 8;
			this->labelHumidity->Text = L"label5";
			// 
			// labelWeatherCode
			// 
			this->labelWeatherCode->AutoSize = true;
			this->labelWeatherCode->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelWeatherCode->Location = System::Drawing::Point(76, 49);
			this->labelWeatherCode->Name = L"labelWeatherCode";
			this->labelWeatherCode->Size = System::Drawing::Size(62, 25);
			this->labelWeatherCode->TabIndex = 9;
			this->labelWeatherCode->Text = L"label5";
			// 
			// WeatherCard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->Controls->Add(this->pictureBoxCard);
			this->Controls->Add(this->labelWeatherCode);
			this->Controls->Add(this->labelHumidity);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->labelWind);
			this->Controls->Add(this->labelTempMin);
			this->Controls->Add(this->labelTempMax);
			this->Controls->Add(this->labelDate);
			this->Margin = System::Windows::Forms::Padding(10, 5, 10, 5);
			this->Name = L"WeatherCard";
			this->Size = System::Drawing::Size(223, 519);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxCard))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
