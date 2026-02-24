namespace lab1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            panel1 = new Panel();
            panel2 = new Panel();
            panel3 = new Panel();
            batton_again = new Button();
            exit = new Button();
            label10 = new Label();
            progressBarSpeedAttack_enemy = new ProgressBar();
            progressBarSpeedAttack_player = new ProgressBar();
            label9 = new Label();
            label8 = new Label();
            label3 = new Label();
            label2 = new Label();
            progressBarArmor_enemy = new ProgressBar();
            progressBarArmor_player = new ProgressBar();
            progressBarHP_enemy = new ProgressBar();
            progressBarHP_player = new ProgressBar();
            richTextBox1 = new RichTextBox();
            Attack_batton = new Button();
            pictureBox5 = new PictureBox();
            pictureBox4 = new PictureBox();
            pictureBox2 = new PictureBox();
            fight_swordsman_batton = new Button();
            fight_archer_batton = new Button();
            fight_warrior_batton = new Button();
            label17 = new Label();
            label18 = new Label();
            label19 = new Label();
            label20 = new Label();
            label21 = new Label();
            label12 = new Label();
            label13 = new Label();
            label14 = new Label();
            label15 = new Label();
            label16 = new Label();
            label7 = new Label();
            label6 = new Label();
            label5 = new Label();
            label4 = new Label();
            label1 = new Label();
            pictureBox1 = new PictureBox();
            pictureBox3 = new PictureBox();
            timer1 = new System.Windows.Forms.Timer(components);
            panel1.SuspendLayout();
            panel2.SuspendLayout();
            panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox5).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox4).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).BeginInit();
            SuspendLayout();
            // 
            // panel1
            // 
            panel1.BackColor = SystemColors.ActiveCaptionText;
            panel1.BackgroundImage = Properties.Resources.background_img;
            panel1.Controls.Add(panel2);
            panel1.Controls.Add(pictureBox2);
            panel1.Controls.Add(fight_swordsman_batton);
            panel1.Controls.Add(fight_archer_batton);
            panel1.Controls.Add(fight_warrior_batton);
            panel1.Controls.Add(label17);
            panel1.Controls.Add(label18);
            panel1.Controls.Add(label19);
            panel1.Controls.Add(label20);
            panel1.Controls.Add(label21);
            panel1.Controls.Add(label12);
            panel1.Controls.Add(label13);
            panel1.Controls.Add(label14);
            panel1.Controls.Add(label15);
            panel1.Controls.Add(label16);
            panel1.Controls.Add(label7);
            panel1.Controls.Add(label6);
            panel1.Controls.Add(label5);
            panel1.Controls.Add(label4);
            panel1.Controls.Add(label1);
            panel1.Controls.Add(pictureBox1);
            panel1.Controls.Add(pictureBox3);
            panel1.Location = new Point(-1, 0);
            panel1.Name = "panel1";
            panel1.Size = new Size(1201, 874);
            panel1.TabIndex = 0;
            // 
            // panel2
            // 
            panel2.BackColor = SystemColors.ControlText;
            panel2.BackgroundImage = Properties.Resources.background_fight;
            panel2.BackgroundImageLayout = ImageLayout.Stretch;
            panel2.Controls.Add(panel3);
            panel2.Controls.Add(progressBarSpeedAttack_enemy);
            panel2.Controls.Add(progressBarSpeedAttack_player);
            panel2.Controls.Add(label9);
            panel2.Controls.Add(label8);
            panel2.Controls.Add(label3);
            panel2.Controls.Add(label2);
            panel2.Controls.Add(progressBarArmor_enemy);
            panel2.Controls.Add(progressBarArmor_player);
            panel2.Controls.Add(progressBarHP_enemy);
            panel2.Controls.Add(progressBarHP_player);
            panel2.Controls.Add(richTextBox1);
            panel2.Controls.Add(Attack_batton);
            panel2.Controls.Add(pictureBox5);
            panel2.Controls.Add(pictureBox4);
            panel2.Location = new Point(0, 3);
            panel2.Name = "panel2";
            panel2.Size = new Size(1201, 871);
            panel2.TabIndex = 33;
            // 
            // panel3
            // 
            panel3.BackColor = SystemColors.GradientActiveCaption;
            panel3.Controls.Add(batton_again);
            panel3.Controls.Add(exit);
            panel3.Controls.Add(label10);
            panel3.Location = new Point(312, 260);
            panel3.Name = "panel3";
            panel3.Size = new Size(571, 286);
            panel3.TabIndex = 44;
            // 
            // batton_again
            // 
            batton_again.BackColor = SystemColors.Desktop;
            batton_again.BackgroundImage = Properties.Resources.background_fight;
            batton_again.FlatStyle = FlatStyle.Flat;
            batton_again.Font = new Font("Courier New", 14F, FontStyle.Bold, GraphicsUnit.Point, 204);
            batton_again.ForeColor = SystemColors.Info;
            batton_again.Location = new Point(342, 174);
            batton_again.Name = "batton_again";
            batton_again.Size = new Size(193, 68);
            batton_again.TabIndex = 2;
            batton_again.Text = "Снова";
            batton_again.UseVisualStyleBackColor = false;
            batton_again.Click += batton_again_Click;
            // 
            // exit
            // 
            exit.BackColor = SystemColors.ActiveCaptionText;
            exit.BackgroundImage = Properties.Resources.background_img;
            exit.FlatStyle = FlatStyle.Flat;
            exit.Font = new Font("Courier New", 14F, FontStyle.Bold, GraphicsUnit.Point, 204);
            exit.ForeColor = SystemColors.Info;
            exit.Location = new Point(35, 174);
            exit.Name = "exit";
            exit.Size = new Size(193, 68);
            exit.TabIndex = 1;
            exit.Text = "Выход";
            exit.UseVisualStyleBackColor = false;
            exit.Click += exit_Click;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Font = new Font("Courier New", 36F, FontStyle.Bold, GraphicsUnit.Point, 204);
            label10.ForeColor = SystemColors.Info;
            label10.Location = new Point(0, 40);
            label10.Name = "label10";
            label10.Size = new Size(336, 82);
            label10.TabIndex = 0;
            label10.Text = "label10";
            // 
            // progressBarSpeedAttack_enemy
            // 
            progressBarSpeedAttack_enemy.ForeColor = SystemColors.Desktop;
            progressBarSpeedAttack_enemy.Location = new Point(833, 537);
            progressBarSpeedAttack_enemy.Maximum = 1000;
            progressBarSpeedAttack_enemy.Name = "progressBarSpeedAttack_enemy";
            progressBarSpeedAttack_enemy.Size = new Size(343, 19);
            progressBarSpeedAttack_enemy.Step = 1;
            progressBarSpeedAttack_enemy.Style = ProgressBarStyle.Continuous;
            progressBarSpeedAttack_enemy.TabIndex = 43;
            progressBarSpeedAttack_enemy.Value = 1000;
            // 
            // progressBarSpeedAttack_player
            // 
            progressBarSpeedAttack_player.ForeColor = SystemColors.Desktop;
            progressBarSpeedAttack_player.Location = new Point(22, 537);
            progressBarSpeedAttack_player.Maximum = 1000;
            progressBarSpeedAttack_player.Name = "progressBarSpeedAttack_player";
            progressBarSpeedAttack_player.Size = new Size(340, 19);
            progressBarSpeedAttack_player.Step = 1;
            progressBarSpeedAttack_player.Style = ProgressBarStyle.Continuous;
            progressBarSpeedAttack_player.TabIndex = 42;
            progressBarSpeedAttack_player.Value = 1000;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Courier New", 9F, FontStyle.Bold, GraphicsUnit.Point, 204);
            label9.ForeColor = SystemColors.Info;
            label9.Location = new Point(11, 57);
            label9.Name = "label9";
            label9.Size = new Size(43, 21);
            label9.TabIndex = 41;
            label9.Text = "ARM";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Courier New", 9F, FontStyle.Bold, GraphicsUnit.Point, 204);
            label8.ForeColor = SystemColors.Info;
            label8.Location = new Point(1144, 57);
            label8.Name = "label8";
            label8.Size = new Size(43, 21);
            label8.TabIndex = 40;
            label8.Text = "ARM";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Courier New", 9F, FontStyle.Bold, GraphicsUnit.Point, 204);
            label3.ForeColor = SystemColors.Info;
            label3.Location = new Point(22, 31);
            label3.Name = "label3";
            label3.Size = new Size(32, 21);
            label3.TabIndex = 39;
            label3.Text = "HP";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Courier New", 9F, FontStyle.Bold, GraphicsUnit.Point, 204);
            label2.ForeColor = SystemColors.Info;
            label2.Location = new Point(1144, 30);
            label2.Name = "label2";
            label2.Size = new Size(32, 21);
            label2.TabIndex = 38;
            label2.Text = "HP";
            // 
            // progressBarArmor_enemy
            // 
            progressBarArmor_enemy.ForeColor = SystemColors.Desktop;
            progressBarArmor_enemy.Location = new Point(836, 59);
            progressBarArmor_enemy.Maximum = 1000;
            progressBarArmor_enemy.Name = "progressBarArmor_enemy";
            progressBarArmor_enemy.Size = new Size(300, 19);
            progressBarArmor_enemy.Step = 1;
            progressBarArmor_enemy.Style = ProgressBarStyle.Continuous;
            progressBarArmor_enemy.TabIndex = 37;
            progressBarArmor_enemy.Value = 1000;
            // 
            // progressBarArmor_player
            // 
            progressBarArmor_player.ForeColor = SystemColors.Desktop;
            progressBarArmor_player.Location = new Point(62, 59);
            progressBarArmor_player.Maximum = 1000;
            progressBarArmor_player.Name = "progressBarArmor_player";
            progressBarArmor_player.Size = new Size(300, 19);
            progressBarArmor_player.Step = 1;
            progressBarArmor_player.Style = ProgressBarStyle.Continuous;
            progressBarArmor_player.TabIndex = 36;
            progressBarArmor_player.Value = 1000;
            // 
            // progressBarHP_enemy
            // 
            progressBarHP_enemy.BackColor = SystemColors.InactiveCaptionText;
            progressBarHP_enemy.ForeColor = SystemColors.ControlText;
            progressBarHP_enemy.Location = new Point(835, 31);
            progressBarHP_enemy.Maximum = 2000;
            progressBarHP_enemy.Name = "progressBarHP_enemy";
            progressBarHP_enemy.Size = new Size(301, 19);
            progressBarHP_enemy.Step = 1;
            progressBarHP_enemy.Style = ProgressBarStyle.Continuous;
            progressBarHP_enemy.TabIndex = 35;
            progressBarHP_enemy.Value = 2000;
            // 
            // progressBarHP_player
            // 
            progressBarHP_player.ForeColor = SystemColors.Desktop;
            progressBarHP_player.Location = new Point(62, 33);
            progressBarHP_player.Maximum = 2000;
            progressBarHP_player.Name = "progressBarHP_player";
            progressBarHP_player.Size = new Size(300, 19);
            progressBarHP_player.Step = 1;
            progressBarHP_player.Style = ProgressBarStyle.Continuous;
            progressBarHP_player.TabIndex = 34;
            progressBarHP_player.Value = 2000;
            // 
            // richTextBox1
            // 
            richTextBox1.BackColor = SystemColors.InactiveCaptionText;
            richTextBox1.BorderStyle = BorderStyle.None;
            richTextBox1.Font = new Font("Courier New", 12F, FontStyle.Bold, GraphicsUnit.Point, 204);
            richTextBox1.ForeColor = Color.BlanchedAlmond;
            richTextBox1.Location = new Point(232, 579);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.ScrollBars = RichTextBoxScrollBars.None;
            richTextBox1.Size = new Size(771, 105);
            richTextBox1.TabIndex = 33;
            richTextBox1.Text = "";
            // 
            // Attack_batton
            // 
            Attack_batton.BackColor = SystemColors.InfoText;
            Attack_batton.FlatStyle = FlatStyle.Flat;
            Attack_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
            Attack_batton.ForeColor = Color.LightSalmon;
            Attack_batton.Image = Properties.Resources.background_lable;
            Attack_batton.Location = new Point(469, 699);
            Attack_batton.Name = "Attack_batton";
            Attack_batton.Size = new Size(306, 90);
            Attack_batton.TabIndex = 32;
            Attack_batton.Text = "АТАКА!";
            Attack_batton.UseVisualStyleBackColor = false;
            Attack_batton.Click += Attack_batton_Click;
            // 
            // pictureBox5
            // 
            pictureBox5.BackgroundImageLayout = ImageLayout.Center;
            pictureBox5.BorderStyle = BorderStyle.FixedSingle;
            pictureBox5.Image = Properties.Resources.Enemy;
            pictureBox5.Location = new Point(836, 93);
            pictureBox5.Name = "pictureBox5";
            pictureBox5.Size = new Size(340, 430);
            pictureBox5.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox5.TabIndex = 1;
            pictureBox5.TabStop = false;
            // 
            // pictureBox4
            // 
            pictureBox4.BorderStyle = BorderStyle.FixedSingle;
            pictureBox4.Location = new Point(22, 93);
            pictureBox4.Name = "pictureBox4";
            pictureBox4.Size = new Size(340, 430);
            pictureBox4.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox4.TabIndex = 0;
            pictureBox4.TabStop = false;
            // 
            // pictureBox2
            // 
            pictureBox2.BorderStyle = BorderStyle.FixedSingle;
            pictureBox2.Image = Properties.Resources.Archer1;
            pictureBox2.Location = new Point(452, 84);
            pictureBox2.Name = "pictureBox2";
            pictureBox2.Size = new Size(319, 365);
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox2.TabIndex = 4;
            pictureBox2.TabStop = false;
            // 
            // fight_swordsman_batton
            // 
            fight_swordsman_batton.BackColor = SystemColors.ActiveCaptionText;
            fight_swordsman_batton.BackgroundImage = Properties.Resources.background_lable;
            fight_swordsman_batton.FlatStyle = FlatStyle.Flat;
            fight_swordsman_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
            fight_swordsman_batton.ForeColor = SystemColors.Info;
            fight_swordsman_batton.Image = Properties.Resources.background_lable;
            fight_swordsman_batton.Location = new Point(871, 717);
            fight_swordsman_batton.Name = "fight_swordsman_batton";
            fight_swordsman_batton.Size = new Size(240, 90);
            fight_swordsman_batton.TabIndex = 32;
            fight_swordsman_batton.Text = "В БОЙ!";
            fight_swordsman_batton.UseVisualStyleBackColor = false;
            fight_swordsman_batton.Click += fight_swordsman_batton_Click;
            // 
            // fight_archer_batton
            // 
            fight_archer_batton.BackColor = SystemColors.ActiveCaptionText;
            fight_archer_batton.BackgroundImage = Properties.Resources.background_lable;
            fight_archer_batton.FlatStyle = FlatStyle.Flat;
            fight_archer_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
            fight_archer_batton.ForeColor = SystemColors.Info;
            fight_archer_batton.Image = Properties.Resources.background_lable;
            fight_archer_batton.Location = new Point(488, 717);
            fight_archer_batton.Name = "fight_archer_batton";
            fight_archer_batton.Size = new Size(240, 90);
            fight_archer_batton.TabIndex = 31;
            fight_archer_batton.Text = "В БОЙ!";
            fight_archer_batton.UseVisualStyleBackColor = false;
            fight_archer_batton.Click += fight_archer_batton_Click;
            // 
            // fight_warrior_batton
            // 
            fight_warrior_batton.BackColor = SystemColors.ActiveCaptionText;
            fight_warrior_batton.BackgroundImage = Properties.Resources.background_lable;
            fight_warrior_batton.FlatStyle = FlatStyle.Flat;
            fight_warrior_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
            fight_warrior_batton.ForeColor = SystemColors.Info;
            fight_warrior_batton.Image = Properties.Resources.background_lable;
            fight_warrior_batton.Location = new Point(97, 717);
            fight_warrior_batton.Name = "fight_warrior_batton";
            fight_warrior_batton.Size = new Size(240, 90);
            fight_warrior_batton.TabIndex = 30;
            fight_warrior_batton.Text = "В БОЙ!";
            fight_warrior_batton.UseVisualStyleBackColor = false;
            fight_warrior_batton.Click += fight_warrior_batton_Click;
            // 
            // label17
            // 
            label17.AutoSize = true;
            label17.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label17.ForeColor = SystemColors.Info;
            label17.Image = Properties.Resources.background_lable;
            label17.ImageAlign = ContentAlignment.BottomCenter;
            label17.Location = new Point(456, 642);
            label17.Name = "label17";
            label17.Size = new Size(233, 25);
            label17.TabIndex = 29;
            label17.Text = "Скорость атаки: 6";
            // 
            // label18
            // 
            label18.AutoSize = true;
            label18.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label18.ForeColor = SystemColors.Info;
            label18.Image = Properties.Resources.background_lable;
            label18.ImageAlign = ContentAlignment.BottomCenter;
            label18.Location = new Point(456, 603);
            label18.Name = "label18";
            label18.Size = new Size(155, 25);
            label18.TabIndex = 28;
            label18.Text = "Защита: 110";
            // 
            // label19
            // 
            label19.AutoSize = true;
            label19.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label19.ForeColor = SystemColors.Info;
            label19.Image = Properties.Resources.background_lable;
            label19.ImageAlign = ContentAlignment.BottomCenter;
            label19.Location = new Point(456, 562);
            label19.Name = "label19";
            label19.Size = new Size(350, 25);
            label19.TabIndex = 27;
            label19.Text = "Суперспособность: +20 урон";
            // 
            // label20
            // 
            label20.AutoSize = true;
            label20.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label20.ForeColor = SystemColors.Info;
            label20.Image = Properties.Resources.background_lable;
            label20.ImageAlign = ContentAlignment.BottomCenter;
            label20.Location = new Point(456, 524);
            label20.Name = "label20";
            label20.Size = new Size(116, 25);
            label20.TabIndex = 26;
            label20.Text = "Урон: 30";
            // 
            // label21
            // 
            label21.AutoSize = true;
            label21.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label21.ForeColor = SystemColors.Info;
            label21.Image = Properties.Resources.background_lable;
            label21.ImageAlign = ContentAlignment.BottomCenter;
            label21.Location = new Point(456, 486);
            label21.Name = "label21";
            label21.Size = new Size(181, 25);
            label21.TabIndex = 25;
            label21.Text = "Здоровье: 190";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label12.ForeColor = SystemColors.Info;
            label12.Image = Properties.Resources.background_lable;
            label12.ImageAlign = ContentAlignment.BottomCenter;
            label12.Location = new Point(835, 642);
            label12.Name = "label12";
            label12.Size = new Size(233, 25);
            label12.TabIndex = 24;
            label12.Text = "Скорость атаки: 4";
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label13.ForeColor = SystemColors.Info;
            label13.Image = Properties.Resources.background_lable;
            label13.ImageAlign = ContentAlignment.BottomCenter;
            label13.Location = new Point(835, 603);
            label13.Name = "label13";
            label13.Size = new Size(155, 25);
            label13.TabIndex = 23;
            label13.Text = "Защита: 120";
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label14.ForeColor = SystemColors.Info;
            label14.Image = Properties.Resources.background_lable;
            label14.ImageAlign = ContentAlignment.BottomCenter;
            label14.Location = new Point(835, 562);
            label14.Name = "label14";
            label14.Size = new Size(350, 25);
            label14.TabIndex = 22;
            label14.Text = "Суперспособность: +2 атака";
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label15.ForeColor = SystemColors.Info;
            label15.Image = Properties.Resources.background_lable;
            label15.ImageAlign = ContentAlignment.BottomCenter;
            label15.Location = new Point(835, 524);
            label15.Name = "label15";
            label15.Size = new Size(116, 25);
            label15.TabIndex = 21;
            label15.Text = "Урон; 40";
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label16.ForeColor = SystemColors.Info;
            label16.Image = Properties.Resources.background_lable;
            label16.ImageAlign = ContentAlignment.BottomCenter;
            label16.Location = new Point(835, 486);
            label16.Name = "label16";
            label16.Size = new Size(181, 25);
            label16.TabIndex = 20;
            label16.Text = "Здоровье: 220";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label7.ForeColor = SystemColors.Info;
            label7.Image = Properties.Resources.background_lable;
            label7.ImageAlign = ContentAlignment.BottomCenter;
            label7.Location = new Point(62, 642);
            label7.Name = "label7";
            label7.Size = new Size(233, 25);
            label7.TabIndex = 14;
            label7.Text = "Скорость атаки: 3";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label6.ForeColor = SystemColors.Info;
            label6.Image = Properties.Resources.background_lable;
            label6.ImageAlign = ContentAlignment.BottomCenter;
            label6.Location = new Point(62, 603);
            label6.Name = "label6";
            label6.Size = new Size(155, 25);
            label6.TabIndex = 13;
            label6.Text = "Защита: 130";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label5.ForeColor = SystemColors.Info;
            label5.Image = Properties.Resources.background_lable;
            label5.ImageAlign = ContentAlignment.BottomCenter;
            label5.Location = new Point(62, 562);
            label5.Name = "label5";
            label5.Size = new Size(324, 25);
            label5.TabIndex = 12;
            label5.Text = "Суперспособность: +25 HP";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label4.ForeColor = SystemColors.Info;
            label4.Image = Properties.Resources.background_lable;
            label4.ImageAlign = ContentAlignment.BottomCenter;
            label4.Location = new Point(62, 524);
            label4.Name = "label4";
            label4.Size = new Size(116, 25);
            label4.TabIndex = 11;
            label4.Text = "Урон: 42";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Courier New", 11F, FontStyle.Bold);
            label1.ForeColor = SystemColors.Info;
            label1.Image = Properties.Resources.background_lable;
            label1.ImageAlign = ContentAlignment.BottomCenter;
            label1.Location = new Point(62, 486);
            label1.Name = "label1";
            label1.Size = new Size(181, 25);
            label1.TabIndex = 8;
            label1.Text = "Здоровье: 240";
            // 
            // pictureBox1
            // 
            pictureBox1.BorderStyle = BorderStyle.FixedSingle;
            pictureBox1.Image = Properties.Resources.Warrior;
            pictureBox1.Location = new Point(62, 84);
            pictureBox1.Name = "pictureBox1";
            pictureBox1.Size = new Size(319, 365);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.TabIndex = 7;
            pictureBox1.TabStop = false;
            // 
            // pictureBox3
            // 
            pictureBox3.BorderStyle = BorderStyle.FixedSingle;
            pictureBox3.Image = Properties.Resources.Swordsman;
            pictureBox3.Location = new Point(835, 84);
            pictureBox3.Name = "pictureBox3";
            pictureBox3.Size = new Size(319, 365);
            pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox3.TabIndex = 5;
            pictureBox3.TabStop = false;
            // 
            // timer1
            // 
            timer1.Tick += timer1_Tick;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1202, 872);
            Controls.Add(panel1);
            Name = "Form1";
            Text = "Form1";
            panel1.ResumeLayout(false);
            panel1.PerformLayout();
            panel2.ResumeLayout(false);
            panel2.PerformLayout();
            panel3.ResumeLayout(false);
            panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)pictureBox5).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox4).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox2).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox1).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBox3).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Panel panel1;
        private PictureBox pictureBox3;
        private PictureBox pictureBox2;
        private PictureBox pictureBox1;
        private Label label17;
        private Label label18;
        private Label label19;
        private Label label20;
        private Label label21;
        private Label label12;
        private Label label13;
        private Label label14;
        private Label label15;
        private Label label16;
        private Label label7;
        private Label label6;
        private Label label5;
        private Label label4;
        private Label label1;
        private Button fight_warrior_batton;
        private Button fight_swordsman_batton;
        private Button fight_archer_batton;
        private Panel panel2;
        private PictureBox pictureBox5;
        private PictureBox pictureBox4;
        private Button Attack_batton;
        private RichTextBox richTextBox1;
        private ProgressBar progressBarHP_enemy;
        private ProgressBar progressBarHP_player;
        private Label label2;
        private ProgressBar progressBarArmor_enemy;
        private ProgressBar progressBarArmor_player;
        private Label label9;
        private Label label8;
        private Label label3;
        private ProgressBar progressBarSpeedAttack_enemy;
        private ProgressBar progressBarSpeedAttack_player;
        private System.Windows.Forms.Timer timer1;
        private Panel panel3;
        private Label label10;
        private Button batton_again;
        private Button exit;
    }
}
