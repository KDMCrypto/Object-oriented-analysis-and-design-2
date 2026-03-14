#include "WeatherLogic.h"
#include "WeatherCard.h"
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

	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: int selectedDays = 3;
	private: String^ cityName = "";

	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ labelCity;
	private: System::Windows::Forms::Panel^ panelOneDay;

	private: System::Windows::Forms::Label^ labelWeatherCodeOneDAY;
	private: System::Windows::Forms::Label^ labelHumidityOneDAY;


	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ labelWindOneDAY;

	private: System::Windows::Forms::Label^ labelTempMinOneDAY;

	private: System::Windows::Forms::Label^ labelTempMaxOneDAY;

	private: System::Windows::Forms::Label^ labelDateOneDAY;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button6;


	public:
		RealWeatherService^ service;
		MyForm(void)
		{
			InitializeComponent();
			service = gcnew RealWeatherService();
			HighlightButton(button3);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TabControl^ tabControl1;

	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;

	private: System::Windows::Forms::TextBox^ textBoxCity;

	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;

	protected:

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBoxCity = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->panelOneDay = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelWeatherCodeOneDAY = (gcnew System::Windows::Forms::Label());
			this->labelHumidityOneDAY = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelWindOneDAY = (gcnew System::Windows::Forms::Label());
			this->labelTempMinOneDAY = (gcnew System::Windows::Forms::Label());
			this->labelTempMaxOneDAY = (gcnew System::Windows::Forms::Label());
			this->labelDateOneDAY = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->labelCity = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->panelOneDay->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Courier New", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::Window;
			this->button1->Location = System::Drawing::Point(233, 670);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(372, 94);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Посмотреть погоду";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->ItemSize = System::Drawing::Size(100, 1);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(858, 844);
			this->tabControl1->TabIndex = 4;
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::Color::Transparent;
			this->tabPage2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage2.BackgroundImage")));
			this->tabPage2->Controls->Add(this->button6);
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->button2);
			this->tabPage2->Controls->Add(this->textBoxCity);
			this->tabPage2->Controls->Add(this->button1);
			this->tabPage2->Location = System::Drawing::Point(4, 5);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(850, 835);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Firebrick;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->ForeColor = System::Drawing::SystemColors::Window;
			this->button6->Location = System::Drawing::Point(811, 6);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(36, 32);
			this->button6->TabIndex = 5;
			this->button6->Text = L"X";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button4
			// 
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(482, 281);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(104, 45);
			this->button4->TabIndex = 4;
			this->button4->Text = L"7 дней";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(353, 281);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(104, 45);
			this->button3->TabIndex = 3;
			this->button3->Text = L"3 дня";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click_1);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(233, 281);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(104, 45);
			this->button2->TabIndex = 2;
			this->button2->Text = L"1 день";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// textBoxCity
			// 
			this->textBoxCity->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxCity->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBoxCity->Location = System::Drawing::Point(201, 193);
			this->textBoxCity->Name = L"textBoxCity";
			this->textBoxCity->Size = System::Drawing::Size(422, 39);
			this->textBoxCity->TabIndex = 1;
			// 
			// tabPage3
			// 
			this->tabPage3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabPage3.BackgroundImage")));
			this->tabPage3->Controls->Add(this->flowLayoutPanel1);
			this->tabPage3->Controls->Add(this->panelOneDay);
			this->tabPage3->Controls->Add(this->button5);
			this->tabPage3->Controls->Add(this->labelCity);
			this->tabPage3->Controls->Add(this->pictureBox1);
			this->tabPage3->Controls->Add(this->pictureBox2);
			this->tabPage3->Location = System::Drawing::Point(4, 14);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(850, 826);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->flowLayoutPanel1->Location = System::Drawing::Point(17, 229);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(816, 586);
			this->flowLayoutPanel1->TabIndex = 0;
			this->flowLayoutPanel1->WrapContents = false;
			// 
			// panelOneDay
			// 
			this->panelOneDay->Controls->Add(this->label5);
			this->panelOneDay->Controls->Add(this->label1);
			this->panelOneDay->Controls->Add(this->labelWeatherCodeOneDAY);
			this->panelOneDay->Controls->Add(this->labelHumidityOneDAY);
			this->panelOneDay->Controls->Add(this->label4);
			this->panelOneDay->Controls->Add(this->label3);
			this->panelOneDay->Controls->Add(this->label2);
			this->panelOneDay->Controls->Add(this->labelWindOneDAY);
			this->panelOneDay->Controls->Add(this->labelTempMinOneDAY);
			this->panelOneDay->Controls->Add(this->labelTempMaxOneDAY);
			this->panelOneDay->Controls->Add(this->labelDateOneDAY);
			this->panelOneDay->Location = System::Drawing::Point(35, 157);
			this->panelOneDay->Name = L"panelOneDay";
			this->panelOneDay->Size = System::Drawing::Size(758, 661);
			this->panelOneDay->TabIndex = 5;
			this->panelOneDay->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(149, 221);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(89, 45);
			this->label5->TabIndex = 21;
			this->label5->Text = L"max:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(149, 280);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 45);
			this->label1->TabIndex = 20;
			this->label1->Text = L"min:";
			// 
			// labelWeatherCodeOneDAY
			// 
			this->labelWeatherCodeOneDAY->AutoSize = true;
			this->labelWeatherCodeOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelWeatherCodeOneDAY->Location = System::Drawing::Point(48, 84);
			this->labelWeatherCodeOneDAY->Name = L"labelWeatherCodeOneDAY";
			this->labelWeatherCodeOneDAY->Size = System::Drawing::Size(107, 45);
			this->labelWeatherCodeOneDAY->TabIndex = 19;
			this->labelWeatherCodeOneDAY->Text = L"label5";
			// 
			// labelHumidityOneDAY
			// 
			this->labelHumidityOneDAY->AutoSize = true;
			this->labelHumidityOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHumidityOneDAY->Location = System::Drawing::Point(288, 423);
			this->labelHumidityOneDAY->Name = L"labelHumidityOneDAY";
			this->labelHumidityOneDAY->Size = System::Drawing::Size(107, 45);
			this->labelHumidityOneDAY->TabIndex = 18;
			this->labelHumidityOneDAY->Text = L"label5";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(47, 423);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(235, 45);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Влажность, %:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(47, 157);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(393, 45);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Температура воздуха, °C";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(47, 348);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(191, 45);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Ветер, м/с: ";
			// 
			// labelWindOneDAY
			// 
			this->labelWindOneDAY->AutoSize = true;
			this->labelWindOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelWindOneDAY->Location = System::Drawing::Point(250, 348);
			this->labelWindOneDAY->Name = L"labelWindOneDAY";
			this->labelWindOneDAY->Size = System::Drawing::Size(102, 45);
			this->labelWindOneDAY->TabIndex = 14;
			this->labelWindOneDAY->Text = L"label1";
			// 
			// labelTempMinOneDAY
			// 
			this->labelTempMinOneDAY->AutoSize = true;
			this->labelTempMinOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTempMinOneDAY->Location = System::Drawing::Point(250, 280);
			this->labelTempMinOneDAY->Name = L"labelTempMinOneDAY";
			this->labelTempMinOneDAY->Size = System::Drawing::Size(107, 45);
			this->labelTempMinOneDAY->TabIndex = 13;
			this->labelTempMinOneDAY->Text = L"label2";
			// 
			// labelTempMaxOneDAY
			// 
			this->labelTempMaxOneDAY->AutoSize = true;
			this->labelTempMaxOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTempMaxOneDAY->Location = System::Drawing::Point(250, 221);
			this->labelTempMaxOneDAY->Name = L"labelTempMaxOneDAY";
			this->labelTempMaxOneDAY->Size = System::Drawing::Size(102, 45);
			this->labelTempMaxOneDAY->TabIndex = 12;
			this->labelTempMaxOneDAY->Text = L"label1";
			// 
			// labelDateOneDAY
			// 
			this->labelDateOneDAY->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelDateOneDAY->Location = System::Drawing::Point(48, 16);
			this->labelDateOneDAY->Name = L"labelDateOneDAY";
			this->labelDateOneDAY->Size = System::Drawing::Size(206, 50);
			this->labelDateOneDAY->TabIndex = 10;
			this->labelDateOneDAY->Text = L"label1";
			this->labelDateOneDAY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button5
			// 
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(658, 23);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(172, 55);
			this->button5->TabIndex = 2;
			this->button5->Text = L"Вернутся к поиску";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// labelCity
			// 
			this->labelCity->AutoSize = true;
			this->labelCity->BackColor = System::Drawing::Color::Transparent;
			this->labelCity->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 22, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelCity->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->labelCity->Location = System::Drawing::Point(57, 94);
			this->labelCity->Name = L"labelCity";
			this->labelCity->Size = System::Drawing::Size(179, 60);
			this->labelCity->TabIndex = 1;
			this->labelCity->Text = L"label14";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->ErrorImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.ErrorImage")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(850, 826);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox2->Location = System::Drawing::Point(0, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(850, 826);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(858, 844);
			this->Controls->Add(this->tabControl1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->panelOneDay->ResumeLayout(false);
			this->panelOneDay->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		cityName = this->textBoxCity->Text;
		WeatherData^ resultData = service->getWeather(cityName);

		if (resultData != nullptr) {

			// обновляем форму
			UpdateUI(resultData);

			labelCity->Text = cityName;
			this->tabControl1->SelectedIndex = 1;
		}
	}
	
	private: String^ GetDescriptionOneDay(int code) {
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

	// Функция вывода погоды
	private: void UpdateUI(WeatherData^ data) {
		this->flowLayoutPanel1->SuspendLayout();
		this->flowLayoutPanel1->Controls->Clear();

		if (selectedDays == 1) {
			// Скрываем список, показываем панель
			this->flowLayoutPanel1->Visible = false;
			this->panelOneDay->Visible = true;

			DailyForecast^ d = data->days[0];

			// Заполняем лейблы панели
			this->labelDateOneDAY->Text = d->date;
			this->labelTempMaxOneDAY->Text = d->tempMax.ToString() + "°";
			this->labelTempMinOneDAY->Text = d->tempMin.ToString() + "°";
			this->labelWindOneDAY->Text = d->windSpeed.ToString();
			this->labelHumidityOneDAY->Text = d->humidity.ToString();
			this->labelWeatherCodeOneDAY->Text = GetDescriptionOneDay(d->weatherCode);

		}
		else {
			// Показываем список, скрываем панель
			this->flowLayoutPanel1->Visible = true;
			this->panelOneDay->Visible = false;

			for (int i = 0; i < selectedDays; i++) {
				WeatherCard^ card = gcnew WeatherCard();
				DailyForecast^ d = data->days[i];
				card->SetData(d->date, d->tempMax, d->tempMin, d->windSpeed, d->humidity, d->weatherCode);
				this->flowLayoutPanel1->Controls->Add(card);
			}
		}

		this->flowLayoutPanel1->ResumeLayout();
		this->Text = "Погода в городе " + data->city + (data->fromCache ? " (КЭШ)" : " (СЕТИ)");
	}

	private: void HighlightButton(Button^ activeBtn) {
		button2->BackColor = Color::LightGray;
		button3->BackColor = Color::LightGray;
		button4->BackColor = Color::LightGray;

		activeBtn->BackColor = Color::SkyBlue;
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 7;
		this->panelOneDay->Visible = false;
		this->flowLayoutPanel1->Visible = true;
		HighlightButton(button4);
	}

	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 1;
		flowLayoutPanel1->Visible = false;
		panelOneDay->Visible = true;
		HighlightButton(button2);
	}
	private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 3;
		this->panelOneDay->Visible = false; // Скрываем панель одного дня
		this->flowLayoutPanel1->Visible = true; // Показываем поток
		HighlightButton(button3);
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		this->tabControl1->SelectedIndex = 0;
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}