using System.Runtime.InteropServices;
using System.Xml.Linq;

namespace lab1
{
    public partial class Form1 : Form
    {

        private Character player;
        private Character enemy;

        private Random random = new Random();
        public Form1()
        {
            InitializeComponent();
            panel1.Visible = true;
            panel2.Visible = false;
            panel3.Visible = false;

            SendMessage(progressBarHP_player.Handle, 0x0410, (IntPtr)2, IntPtr.Zero);
            SendMessage(progressBarHP_enemy.Handle, 0x0410, (IntPtr)2, IntPtr.Zero);
            SendMessage(progressBarArmor_player.Handle, 0x0410, (IntPtr)3, IntPtr.Zero);
            SendMessage(progressBarArmor_enemy.Handle, 0x0410, (IntPtr)3, IntPtr.Zero);
            SendMessage(progressBarSpeedAttack_player.Handle, 0x0410, (IntPtr)0, IntPtr.Zero);
            SendMessage(progressBarSpeedAttack_enemy.Handle, 0x0410, (IntPtr)0, IntPtr.Zero);

            // Привязываем событие таймера
            timer1.Interval = 30;
            timer1.Tick += timer1_Tick;
            timer1.Start();
        }


        private void fight_warrior_batton_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
            panel2.Visible = true;
            pictureBox4.Image = Properties.Resources.Warrior;


            Creator My_WarriorCreator = new WarriorCreator();

            player = My_WarriorCreator.createCharacter();
            enemy = new EnemyCreator().createCharacter();

            init_PB();

            richTextBox1.AppendText($"Бой между {player.Name} и {enemy.Name} начался\n");
            richTextBox1.ScrollToCaret();

        }

        private void fight_archer_batton_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
            panel2.Visible = true;
            pictureBox4.Image = Properties.Resources.Archer1;


            Creator My_ArcherCreator = new ArcherCreator();

            player = My_ArcherCreator.createCharacter();
            enemy = new EnemyCreator().createCharacter();

            init_PB();

            richTextBox1.AppendText($"Бой между {player.Name} и {enemy.Name} начался\n");
            richTextBox1.ScrollToCaret();
        }

        private void fight_swordsman_batton_Click(object sender, EventArgs e)
        {
            panel1.Visible = true;
            panel2.Visible = true;
            pictureBox4.Image = Properties.Resources.Swordsman;


            Creator My_SwordsmanCreator = new SwordsmanCreator();

            player = My_SwordsmanCreator.createCharacter();
            enemy = new EnemyCreator().createCharacter();

            init_PB();

            richTextBox1.AppendText($"Бой между {player.Name} и {enemy.Name} начался\n");
            richTextBox1.ScrollToCaret();
        }

        private void Attack_batton_Click(object sender, EventArgs e)
        {
            progressBarSpeedAttack_player.Value = 0;
            Attack_batton.Enabled = false;
            Attack_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
            Attack_batton.Text = "Перезарядка";

            // Шанс 10% на суперспособность игрока
            if (random.Next(1, 101) <= 10)
            {
                richTextBox1.AppendText(player.useAbility());
            }

            // Шанс 45% на случайный блок врага
            if (random.Next(1, 101) <= 45)
            {
                enemy.IsBlocking = true;
                richTextBox1.AppendText($"[{enemy.Name}] инстинктивно закрывается!\n");
            }
            richTextBox1.AppendText(player.attack(enemy));
            UpdateUI();

            if (enemy.Health <= 0)
            {
                timer1.Stop();
                label10.Text = "ПОБЕДА!!!!!!!";
                label10.ForeColor = Color.Orange;
                label10.BackColor = Color.Red;
                panel3.BackColor = Color.Red;
                panel3.Visible = true;
                //MessageBox.Show("Победа!");
            }
        }


        private void EnemyAttack()
        {
            progressBarSpeedAttack_enemy.Value = 0;

            // Шанс 15% на способность врага
            if (random.Next(1, 101) <= 10)
            {
                richTextBox1.AppendText(enemy.useAbility());
            }

            // Шанс 25% на случайный блок игрока
            if (random.Next(1, 101) <= 25)
            {
                player.IsBlocking = true;
                richTextBox1.AppendText($"[{player.Name}] инстинктивно группируется!\n");
            }

            richTextBox1.AppendText(enemy.attack(player));
            UpdateUI();

            if (player.Health <= 0)
            {
                timer1.Stop();
                label10.Text = "ВЫ ПРОИГРАЛИ!";
                label10.ForeColor = Color.Orange;
                label10.BackColor = Color.Red;
                panel3.BackColor = Color.Red;
                panel3.Visible = true;
                //MessageBox.Show("Вы проиграли...");
            }
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, IntPtr w, IntPtr l);

        private void UpdateUI()
        {
            SetBar(progressBarHP_player, player.Health);
            SetBar(progressBarHP_enemy, enemy.Health);
            SetBar(progressBarArmor_player, player.Defense);
            SetBar(progressBarArmor_enemy, enemy.Defense);
            richTextBox1.ScrollToCaret();
        }

        // Проверка границ ProgressBar
        private void SetBar(ProgressBar pb, int val)
        {
            if (val < 0) val = 0;
            if (val > pb.Maximum) pb.Maximum = val; // Если подлечились выше максимума — расширяем полоску

            if (val < pb.Maximum) pb.Value = val + 1;
            pb.Value = val;
        }

        private void init_PB()
        {
            progressBarHP_player.Maximum = player.Health + 1;
            progressBarHP_player.Value = player.Health;

            progressBarArmor_player.Maximum = player.Defense + 1;
            progressBarArmor_player.Value = player.Defense;

            progressBarHP_enemy.Maximum = enemy.Health + 1;
            progressBarHP_enemy.Value = enemy.Health;

            progressBarArmor_enemy.Maximum = enemy.Defense + 1;
            progressBarArmor_enemy.Value = enemy.Defense;

            progressBarSpeedAttack_player.Maximum = 1000;
            progressBarSpeedAttack_player.Value = 1000;
            progressBarSpeedAttack_enemy.Maximum = 1000;
            progressBarSpeedAttack_enemy.Value = 1000;
        }

        private void timer1_Tick(object? sender, EventArgs? e)
        {
            if (player == null || enemy == null || player.Health <= 0 || enemy.Health <= 0)
                return;

            // прогресс бар ИГРОК
            if (progressBarSpeedAttack_player.Value < progressBarSpeedAttack_player.Maximum)
            {
                int newPlayerValue = progressBarSpeedAttack_player.Value + player.SpeedAttack;
                progressBarSpeedAttack_player.Value = Math.Min(newPlayerValue, progressBarSpeedAttack_player.Maximum);
            }

            // Включаем кнопку, когда шкала игрока заполнилась
            if (progressBarSpeedAttack_player.Value >= progressBarSpeedAttack_player.Maximum)
            {
                if (!Attack_batton.Enabled)
                {
                    Attack_batton.Enabled = true;
                    Attack_batton.ForeColor = Color.LightSalmon;
                    Attack_batton.Font = new Font("Courier New", 20F, FontStyle.Bold);
                    Attack_batton.Text = "АТАКА!";
                }
            }

            // прогресс бар ВРАГА
            if (progressBarSpeedAttack_enemy.Value < progressBarSpeedAttack_enemy.Maximum)
            {
                int newEnemyValue = progressBarSpeedAttack_enemy.Value + enemy.SpeedAttack;
                progressBarSpeedAttack_enemy.Value = Math.Min(newEnemyValue, progressBarSpeedAttack_enemy.Maximum);
            }

            // Если шкала врага заполнилась он ударяет
            if (progressBarSpeedAttack_enemy.Value >= progressBarSpeedAttack_enemy.Maximum)
            {
                EnemyAttack();
            }
        }

        private void exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void batton_again_Click(object sender, EventArgs e)
        {
            timer1.Stop();

            panel3.Visible = false;
            panel2.Visible = false;
            panel1.Visible = true;

            richTextBox1.Clear();
            Attack_batton.Enabled = false;

            progressBarHP_player.Value = 0;
            progressBarHP_enemy.Value = 0;
            progressBarSpeedAttack_player.Value = 0;
            progressBarSpeedAttack_enemy.Value = 0;

            player = null;
            enemy = null;

            timer1.Start();
        }

        // класс Персонажа
        public abstract class Character
        {
            public string Name { get; set; }
            public int Health { get; set; }
            public int AttackPower { get; set; }
            public int Defense { get; set; }
            public int SpeedAttack { get; set; }
            public bool IsBlocking { get; set; } = false;
            public Character(string name, int health, int attackPower, int defense, int speedAtteck)
            {
                Name = name;
                Health = health;
                AttackPower = attackPower;
                Defense = defense;
                SpeedAttack = speedAtteck;
            }
            public abstract string attack(Character Object_Enemy);

            public abstract string useAbility();

            public string TakeDamage(int damage)
            {
                int incomingDamage = damage;
                string log = "";

                // блок
                if (IsBlocking)
                {
                    incomingDamage /= 2; // Урон режем в 2 раза
                    log += "[БЛОК! Урон снижен] ";
                    IsBlocking = false;
                }

                // Урон идет в Броню
                if (Defense > 0)
                {
                    if (Defense >= incomingDamage)
                    {
                        Defense -= incomingDamage;
                        log += $"Броня поглотила {incomingDamage} урона!\n";
                        return log;
                    }
                    else
                    {
                        int remainingDamage = incomingDamage - Defense;
                        log += $"Броня пробита! (Поглощено {Defense} урона). ";
                        Defense = 0;
                        Health -= remainingDamage; // Остаток летит в HP
                        if (Health < 0) Health = 0;
                        log += $"Здоровье потеряло {remainingDamage} HP!\n";
                        return log;
                    }
                }
                //  Если брони нет, урон идет напрямую в HP
                else
                {
                    Health -= incomingDamage;
                    if (Health < 0) Health = 0;
                    log += $"Получено {incomingDamage} урона здоровью!\n";
                    return log;
                }
            }

        }
        // дочений класс Воин
        public class Warrior : Character
        {
            public Warrior() : base("Воин", 240, 42, 130, 3)
            {
            }
            public override string attack(Character Object_Enemy)
            {
                string result = $"{Name} бьет топором! {Object_Enemy.TakeDamage(AttackPower)}\n";

                return result;
            }

            public override string useAbility()
            {
                int Ability_num = 25;
                Health += Ability_num;
                string result = $"Стработала суперсопсобность, Воин получил + {Ability_num}!\n";

                return result;
            }

        }
        // дочений класс Лучник 
        public class Archer : Character
        {
            public Archer() : base("Лучник", 190, 30, 110, 6)
            {
            }
            public override string attack(Character Object_Enemy)
            {
                string result = $"{Name} попадает из лука! {Object_Enemy.TakeDamage(AttackPower)}\n";

                return result;
            }

            public override string useAbility()
            {
                int attackPower_num = 20;
                AttackPower += attackPower_num;
                string result = $"У {Name} Стработала суперсопсобность, его урон увеличен на {attackPower_num}!\n";

                return result;
            }

        }

        // дочений класс Мечник
        public class Swordsman : Character
        {
            public Swordsman() : base("Мечник", 220, 40, 125, 4)
            {

            }
            public override string attack(Character Object_Enemy)
            {
                string result = $"{Name} бьет мечем противника! {Object_Enemy.TakeDamage(AttackPower)}\n";

                return result;
            }

            public override string useAbility()
            {
                int SpeedAttack_num = 2;
                SpeedAttack += SpeedAttack_num;
                string result = $"У {Name} Стработала суперсопсобность, скорость его атаки теперь составляет {SpeedAttack}!\n";

                return result;
            }

        }

        public class Enemy : Character
        {
            public Enemy() : base("Враг", 215, 33, 115, 3)
            {
            }
            public override string attack(Character Object_Enemy)
            {
                string result = $"{Name} наносит удар! {Object_Enemy.TakeDamage(AttackPower)}";

                return result;
            }

            public override string useAbility()
            {
                int SpeedAttack_num = 2;
                int Ability_num = 40;

                Health += Ability_num;
                SpeedAttack += SpeedAttack_num;

                string result = $"У {Name} Стработала суперсопсобность, скорость его атаки теперь составляет {SpeedAttack} и еще у него повысилось здоровье на {Ability_num}, теперь его не победить!\n";

                return result;
            }



        }

        // Фабрика 
        public abstract class Creator
        {
            public abstract Character createCharacter();

        }

        // создатель война
        public class WarriorCreator : Creator
        {
            public override Character createCharacter()
            {
                return new Warrior();
            }
        }

        // создатель лучника
        public class ArcherCreator : Creator
        {
            public override Character createCharacter()
            {
                return new Archer();
            }
        }

        // создатель мечника
        public class SwordsmanCreator : Creator
        {
            public override Character createCharacter()
            {
                return new Swordsman();
            }
        }

        // создатель Врага
        public class EnemyCreator : Creator
        {
            public override Character createCharacter()
            {
                return new Enemy();
            }
        }

    }
}