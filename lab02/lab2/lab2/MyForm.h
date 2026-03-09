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
	private: WeatherData^ lastData = nullptr;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ labelCity;
	public:
		ProxyWeather^ service;
		MyForm(void)
		{
			InitializeComponent();

			service = gcnew ProxyWeather();
			service->OnDataReady += gcnew WeatherService::WeatherCallback(this, &MyForm::UpdateUI);

			// 1. Включаем двойную буферизацию для ВСЕХ элементов на вкладке
			this->DoubleBuffered = true;
			this->tabPage3->GetType()->GetProperty("DoubleBuffered",
				System::Reflection::BindingFlags::Instance | System::Reflection::BindingFlags::NonPublic)
				->SetValue(this->tabPage3, true, nullptr);

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
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBoxCity = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->labelCity = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
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
			this->tabControl1->ItemSize = System::Drawing::Size(100, 10);
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
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->button2);
			this->tabPage2->Controls->Add(this->textBoxCity);
			this->tabPage2->Controls->Add(this->button1);
			this->tabPage2->Location = System::Drawing::Point(4, 14);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(850, 826);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
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
			this->tabPage3->Controls->Add(this->button5);
			this->tabPage3->Controls->Add(this->labelCity);
			this->tabPage3->Controls->Add(this->flowLayoutPanel1);
			this->tabPage3->Controls->Add(this->pictureBox1);
			this->tabPage3->Controls->Add(this->pictureBox2);
			this->tabPage3->Location = System::Drawing::Point(4, 14);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(850, 826);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
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
			this->labelCity->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelCity->ForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->labelCity->Location = System::Drawing::Point(57, 94);
			this->labelCity->Name = L"labelCity";
			this->labelCity->Size = System::Drawing::Size(116, 38);
			this->labelCity->TabIndex = 1;
			this->labelCity->Text = L"label14";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->BackColor = System::Drawing::SystemColors::Window;
			this->flowLayoutPanel1->Location = System::Drawing::Point(14, 220);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(816, 586);
			this->flowLayoutPanel1->TabIndex = 0;
			this->flowLayoutPanel1->WrapContents = false;
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		String^ cityName = this->textBoxCity->Text;
		service->getWeather(cityName);

		labelCity->Text = cityName;

		this->tabControl1->SelectedIndex = 1;
	}

		   // Функция вывода погоды
		   void UpdateUI(WeatherData^ data, bool fromCache) {

			   this->lastData = data; // Сохраняем для мгновенного переключения

			   this->flowLayoutPanel1->Controls->Clear();

			   for (int i = 0; i < selectedDays; i++) {
				   WeatherCard^ card = gcnew WeatherCard();

				   DailyForecast^ d = data->days[i];
				   card->SetData(d->date, d->tempMax, d->tempMin, d->windSpeed, d->humidity, d->weatherCode);

				   this->flowLayoutPanel1->Controls->Add(card);
			   }

			   this->flowLayoutPanel1->ResumeLayout(); // Возвращаем отрисовку

			   // Показываем источник данных прямо
			   String^ source = fromCache ? " (из КЭША)" : " (из СЕТИ)";
			   this->Text = "Погода в городе " + data->city + source;

		   }

		   void HighlightButton(Button^ activeBtn) {
			   button2->BackColor = Color::LightGray;
			   button3->BackColor = Color::LightGray;
			   button4->BackColor = Color::LightGray;

			   activeBtn->BackColor = Color::SkyBlue;
		   }

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 7;
		HighlightButton(button4);
		if (lastData != nullptr) UpdateUI(lastData, true);
	}

	private: System::Void button2_Click_1(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 1;
		HighlightButton(button2);
		if (lastData != nullptr) UpdateUI(lastData, true);
	}
	private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {
		selectedDays = 3;
		HighlightButton(button3);
		if (lastData != nullptr) UpdateUI(lastData, true);
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		this->tabControl1->SelectedIndex = 0;

	}

	};
}