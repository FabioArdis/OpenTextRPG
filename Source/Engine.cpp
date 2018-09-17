#include "Engine.h"

#define waitkey rlutil::anykey("Press any button to continue...")

using namespace std;

using namespace rlutil;

Player iPlayer;
Dummy iDummy;
Enemy rEnemy;
Location iLocation;

ifstream Save1I;
ofstream Save1O;

Engine::Engine(){}

void Engine::Battle(Enemy enemy)
{
    cls();
    enemy.hp = enemy.maxHp;
    setColor(5);
    cout << enemy.name << " appears!\n";
    int enemyAttack = 1;
    int selection = 1;
    int escape;
    waitkey;
    resetColor();
    while(enemy.hp > 0 && iPlayer.hp > 0 && escape != 1)
    {
		cls();
        setColor(2);
        cout << iPlayer.name << "'s life = " << iPlayer.hp << endl;
        setColor(4);
        cout << enemy.name << "'s life = " << enemy.hp << endl << endl;
        resetColor();
		#ifndef __SWITCH__
        cout << "What's your next move?\n\t";
        cout << "1-Attack\n\t2-Magic\n\t3-Escape\n\t4-Inventory\n\n";
        cin >> selection;
		#else
		cout << "What's your next move?\n\t";
        cout << "L-Attack\n\tR-Magic\n\tZL-Escape\n\tZR-Inventory\n\n";
		selection = getnum();
		#endif
        switch (selection)
        {
        case(1):
            enemy.hp -= iPlayer.atk;
            setColor(1);
            cout << enemy.name << " takes " << iPlayer.atk << " damage!\n";
            enemyAttack = rand() % 2;
            if(enemyAttack == 1 && enemy.hp > 0)
            {
                iPlayer.hp -= enemy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << enemy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << enemy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        case(2):
            Magic(enemy);
            enemyAttack = rand() % 2;
            if(enemyAttack == 1 && enemy.hp > 0)
            {
                iPlayer.hp -= enemy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << enemy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << enemy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        case(3):
            escape = rand() % 4;
            if (escape == 1)
            {
                setColor(9);
                cout << "You successfully escaped.\n";
                resetColor();
                getch();
            }
            else
            {
                cout << "The enemy blocks your path!\n";
                enemyAttack = rand() % 2;
                if(enemyAttack == 1 && enemy.hp > 0)
                {
                    iPlayer.hp -= enemy.atk;
                    setColor(4);
                    cout << iPlayer.name << " takes " << enemy.atk << " damage!\n";
                    resetColor();
                    getch();
                }
                else
                {
                    setColor(3);
                    cout << enemy.name << "'s attack missed!";
                    resetColor();
                    getch();
                }
            }
            break;
        case(4):
            cout << "Sorry, the inventory couldn't reach this version.\n";
            getch();
            break;
        default:
            enemyAttack = rand() % 2;
            if(enemyAttack == 1 && enemy.hp > 0)
            {
                iPlayer.hp -= enemy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << enemy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << enemy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        }
    }
    if(iPlayer.hp <= 0)
    {
        setColor(5);
        cout << "You died.\n";
        resetColor();
        getch();
        Start();
    }
	cls();
    if(escape != 1)
    {
        setColor(2);
        cout << enemy.name << " dies.\n";
        resetColor();
        getch();
        iPlayer.exp += enemy.exp;
        setColor(14);
        cout << "\n" << iPlayer.name << " gains " << enemy.exp << " exp points.\n\n"
             << iPlayer.name << " recovers " << 2 * iPlayer.level << " health points.\n\n";
        iPlayer.hp += (iPlayer.level * 2);
        if(iPlayer.hp > iPlayer.maxHp)
            iPlayer.hp = iPlayer.maxHp;
        resetColor();
        getch();
		cls();
        while(iPlayer.exp >= iPlayer.nextlevel)
            PlayerUp();
        Save();
    }
}

void Engine::Battle(Dummy dummy)
{
	cls();
    dummy.hp = dummy.maxHp;
    setColor(5);
    cout << dummy.name << " appears!\n";
    int dummyAttack = 1;
    int selection = 1;
    int escape;
    waitkey;
    resetColor();
    while(dummy.hp > 0 && iPlayer.hp > 0 && escape != 1)
    {
		cls();
        setColor(2);
        cout << iPlayer.name << "'s life = " << iPlayer.hp << endl;
        setColor(4);
        cout << dummy.name << "'s life = " << dummy.hp << endl << endl;
        resetColor();
        cout << "What's your next move?\n\t";
		#ifndef __SWITCH__
        cout << "1-Attack\n\t2-Magic\n\t3-Escape\n\t4-Inventory\n\n";
        cin >> selection;
		#else
		cout << "L-Attack\n\tR-Magic\n\tZL-Escape\n\tZR-Inventory\n\n";
		selection = getnum();
		#endif
        switch (selection)
        {
        case(1):
            dummy.hp -= iPlayer.atk;
            setColor(1);
            cout << dummy.name << " takes " << iPlayer.atk << " damage!\n";
            dummyAttack = rand() % 2;
            if(dummyAttack == 1 && dummy.hp > 0)
            {
                iPlayer.hp -= dummy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << dummy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << dummy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        case(2):
            Magic(dummy);
            dummyAttack = rand() % 2;
            if(dummyAttack == 1 && dummy.hp > 0)
            {
                iPlayer.hp -= dummy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << dummy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << dummy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        case(3):
            escape = rand() % 4;
            if (escape == 1)
            {
                setColor(9);
                cout << "You successfully escaped.\n";
                resetColor();
                getch();
                break;
            }
            else
            {
                cout << "The enemy blocks your path!\n";
                dummyAttack = rand() % 2;
                if(dummyAttack == 1 && dummy.hp > 0)
                {
                    iPlayer.hp -= dummy.atk;
                    setColor(4);
                    cout << iPlayer.name << " takes " << dummy.atk << " damage!\n";
                    resetColor();
                    getch();
                }
                else
                {
                    setColor(3);
                    cout << dummy.name << "'s attack missed!";
                    resetColor();
                    getch();
                }
            }
            break;
        case(4):
            cout << "Sorry, the inventory couldn't reach this version.\nn";
            getch();
            break;
        default:
            dummyAttack = rand() % 2;
            if(dummyAttack == 1 && dummy.hp > 0)
            {
                iPlayer.hp -= dummy.atk;
                setColor(4);
                cout << iPlayer.name << " takes " << dummy.atk << " damage!\n";
                resetColor();
                getch();
            }
            else
            {
                setColor(3);
                cout << dummy.name << "'s attack missed!";
                resetColor();
                getch();
            }
            break;
        }
    }
    if(iPlayer.hp <= 0)
    {
        setColor(5);
        cout << "You died.\n";
        resetColor();
        getch();
        exit(0);
    }
	cls();
    if(escape != 1)
    {
        setColor(2);
        cout << dummy.name << " dies.\n";
        resetColor();
        getch();
        iPlayer.exp += dummy.exp;
        setColor(14);
        cout << "\n" << iPlayer.name << " gains " << dummy.exp << " exp points.\n\n"
             << iPlayer.name << " recovers " << 2 * iPlayer.level << " health points.\n\n";
        iPlayer.hp += (iPlayer.level * 2);
        if(iPlayer.hp > iPlayer.maxHp)
            iPlayer.hp = iPlayer.maxHp;
        resetColor();
        getch();
		cls();
        while(iPlayer.exp >= iPlayer.nextlevel)
            PlayerUp();
    }
}

void Engine::Start()
{
    hidecursor();
    srand(time(NULL));
    saveDefaultColor();
	cls();
    int selection = 1;
	#ifndef __SWITCH__
	cout << "Welcome to OpenTextRPG.\n\n";
	cout << "Select an option.\n\n";
	setColor(2);
	cout << "\t1-Play\n";
	cout << "\t2-Random Battle\n";
	resetColor();
	cout << "\t3-Load save file\n";
	cout << "\t4-Exit\n\n";
	cin >> selection;
	#else
	cout << "Welcome to OpenTextRPG.\n\n";
	cout << "Select an option.\n\n";
	setColor(2);
	cout << "\tL-Play\n";
	cout << "\tR-Random Battle\n";
	resetColor();
	cout << "\tZL-Load save file\n";
	cout << "\tZR-Exit\n\n";
	selection = getnum();
	#endif
    switch(selection)
    {
    case(1):
        Play();
        break;
    case(2):
        Randomize();
        break;
    case(3):
        Load();
        break;
    case(4):
        exit(0);
        break;
    default:
        cin.clear();
        Start();
        break;
    }
}

void Engine::Play()
{
	int selection = 1;

	cls();
	#ifndef __SWITCH__
    cout << "Choose a name.\n\n";
    cin.ignore();
    getline(cin, iPlayer.name);
    cout << "\nChoose a surname.\n\n";
    getline(cin, iPlayer.surname);
    cout << "\nSo, you are " << iPlayer.name << " " << iPlayer.surname << "?\n\n"
         << "Press 1 for yes, 0 for no.\n\n";
    cin >> selection;
	#else
	iPlayer.name = "Test";
	iPlayer.surname = "STest";
	cout << "\nSo, you are " << iPlayer.name << " " << iPlayer.surname << "?\n\n"
         << "Press L for yes, R for no.\n\n";
	selection = getnum();
	#endif
    switch(selection)
    {
    case(1):
        ChooseClass();
        break;
    default:
        Play();
        break;
    }
}

void Engine::ChooseClass()
{
	cls();
	int selection = 1;
	#ifndef __SWITCH__
	cout << "Ok, now choose a class.\n\n\t1-Archer\n\t2-Knight\n\t3-Mage\n\t4-Warrior\n";
	cin >> selection;
	#else
	cout << "Ok, now choose a class.\n\n\tL-Archer\n\tR-Knight\n\tZL-Mage\n\tZR-Warrior\n";
	selection = getnum();
	#endif
	switch(selection)
	{
    case(1):
        iPlayer.playerclass = "Archer";
        iPlayer.hp = 20;
        iPlayer.atk = 25;
        iPlayer.mag = 10;
        iPlayer.maxHp = iPlayer.hp;
        break;
    case(2):
        iPlayer.playerclass = "Knight";
        iPlayer.hp = 70;
        iPlayer.atk = 25;
        iPlayer.mag = 20;
        iPlayer.maxHp = iPlayer.hp;
        break;
    case(3):
        iPlayer.playerclass = "Archer";
        iPlayer.hp = 30;
        iPlayer.atk = 10;
        iPlayer.mag = 30;
        iPlayer.maxHp = iPlayer.hp;
        break;
    case(4):
        iPlayer.playerclass = "Warrior";
        iPlayer.hp = 50;
        iPlayer.atk = 45;
        iPlayer.mag = 10;
        iPlayer.maxHp = iPlayer.hp;
        break;
    default:
        ChooseClass();
        break;
	}
	int confirm;
	#ifndef __SWITCH__
	cout << "\nSo, you are " << iPlayer.name << " " << iPlayer.surname << ", the " << iPlayer.playerclass << "?\n\nPress 1 for yes, 0 for no.\n\n";
	cin >> confirm;
	#else
	cout << "\nSo, you are " << iPlayer.name << " " << iPlayer.surname << ", the " << iPlayer.playerclass << "?\n\nPress L for yes, R for no.\n\n";
	confirm = getnum();
	#endif
	if(confirm)
        Summary();
    else
        ChooseClass();
}

void Engine::Summary()
{
	cls();
	int selection = 1;
	cout << "This is a summary of your choices\n\nName: " << iPlayer.name << "\nSurname: " << iPlayer.surname;
	setColor(14);
	cout << "\nClass: " << iPlayer.playerclass;
	setColor(2);
	cout << "\nHealth Points: " << iPlayer.hp;
	setColor(4);
	cout << "\nAttack: " << iPlayer.atk;
	setColor(1);
	cout << "\nMagic: " << iPlayer.mag << "\n\n";
	resetColor();
	#ifndef __SWITCH__
	cout << "Do you want to edit something?\n\t1-Name and Surname\n\t2-Class\n\t3-Go ahead\n\t4-Main Menu\n\n";
	cin >> selection;
	#else
	cout << "Do you want to edit something?\n\tL-Name and Surname\n\tR-Class\n\tZL-Go ahead\n\tZR-Main Menu\n\n";
	selection = getnum();
	#endif
	switch (selection)
	{
	case(1):
		Play();
		break;
	case(2):
		ChooseClass();
		break;
	case(3):
        TrainingZone1();
        Battle(iDummy);
		break;
	case(4):
		Start();
		break;
	default:
		Summary();
		break;
	}
}

void Engine::TrainingZone1()
{
	cls();
    int selection = 1;
    cout << "Trainer\nWelcome to the Training Zone, I will teach you how to survive out of the safe\nzones.\n";
    getch();
    #ifndef __SWITCH__
	cls();
	#endif
	#ifndef __SWITCH__
    cout << "Trainer\nNow, tell me what do you want to learn, please.\n\t1-Attack\n\t2-Magic\n\t3-Special\n\t4-Nothing, thanks.\n";
    cin >> selection;
	#else
	cout << "Trainer\nNow, tell me what do you want to learn, please.\n\tL-Attack\n\tR-Magic\n\tZL-Special\n\tZR-Nothing, thanks.\n";
	selection = getnum();
	#endif
	switch (selection)
	{
    case(1):
		cls();
		cout << "Trainer\nWhen attacked by one or more enemies, you should give it right back to 'em.\nChoose Attack when the Battle Menu shows up";
		getch();
		TrainingZone1();
        break;
    case(2):
		cls();
		cout << "Trainer\nUnlike the Attack, the magic has multiple purposes. In fact, magic can\nserve to attack, but also to heal yourself or to confuse the enemy.";
		getch();
		TrainingZone1();
        break;
    case(3):
		cls();
		cout << "Trainer\nAs the name says, they are attacks/spells very powerful that can only be\nused once in battle.";
		getch();
		TrainingZone1();
        break;
    case(4):
		TrainingZone2();
        break;
    default:
        TrainingZone1();
        break;
	}
}

void Engine::TrainingZone2()
{
	cls();
	int selection = 1;
	#ifndef __SWITCH__
	cout << "Trainer\nThis is a dummy, you can use it when you want to train your combat skills.\n"
         << "When you're ready, press 1 to start the battle, or press 0 to go back.\n";
	cin >> selection;
	#else
	cout << "Trainer\nThis is a dummy, you can use it when you want to train your combat skills.\n"
         << "When you're ready, press L to start the battle, or press R to go back.\n";
	selection = getnum();
	#endif
	if (selection == 1)
	{
	    Battle(iDummy);
		cls();
	    cout << "Congratulations! You can now go wherever you want in this little map with random encounters.";
	    getch();
	    iPlayer.actualZone = 3;
	    Engine::UpdateDungeon(iLocation.Dungeon1);
	}
	else
        TrainingZone1();
}

void Engine::Save()
{
    int selection = 0;
	cls();
	#ifndef __SWITCH__
    cout << "Do you want to save?\n1-Yes\n0-No\n";
    cin >> selection;
	#else
	cout << "Do you want to save?\nL-Yes\nR-No\n";
    selection = getnum();
	#endif
    if(selection)
    {
        Save1O.open("save1.txt");
        Save1O << iPlayer.name << endl << iPlayer.surname << endl
			<< iPlayer.playerclass << endl << iPlayer.hp << endl
			<< iPlayer.atk << endl << iPlayer.mag << endl
			<< iPlayer.exp << endl << iPlayer.maxHp << endl
			<< iPlayer.level << endl << iPlayer.nextlevel << endl
			<< iPlayer.actualZone << endl;
        cout << "Saved successfully.\n";
        getch();
    }
}

void Engine::Load()
{
    string str;
    cout << "Loading...\n";
	Save1I.open("save1.txt");
	if (getline(Save1I, str))
		iPlayer.name = str;
	if (getline(Save1I, str))
		iPlayer.surname = str;
	if (getline(Save1I, str))
		iPlayer.playerclass = str;
	if (getline(Save1I, str))
		iPlayer.hp = stoi(str);
	if (getline(Save1I, str))
		iPlayer.atk = stoi(str);
	if (getline(Save1I, str))
		iPlayer.mag = stoi(str);
	if (getline(Save1I, str))
		iPlayer.exp = stoi(str);
	if (getline(Save1I, str))
		iPlayer.maxHp = stoi(str);
	if (getline(Save1I, str))
		iPlayer.level = stoi(str);
	if (getline(Save1I, str))
		iPlayer.nextlevel = stoi(str);
	if (getline(Save1I, str))
		iPlayer.actualZone = stoi(str);
	Save1I.close();
	cout << "Loading complete." << endl;
	switch(iPlayer.actualZone)
	{
    case(0):
        TrainingZone1();
        break;
    case(1):
        TrainingZone2();
        break;
    case(2):
        Battle(iDummy);
        break;
    case(3):
        Engine::UpdateDungeon(iLocation.Dungeon1);
        break;
    default:
        cout << "Error, couldn't find the " << iPlayer.actualZone << " zone.\n";
        waitkey;
        Start();
        break;
	}
	waitkey;
}

void Engine::Randomize()
{
	cls();

    rEnemy.name = "Random Enemy";
    iPlayer.name = "Random Player";

    cout << "Randomizing..." << endl;
    srand(time(NULL));

    iPlayer.atk = rand() % 25 + 1;
	iPlayer.hp = rand() % 100 + 1;
	iPlayer.mag = rand() % 30 + 1;
	iPlayer.maxHp = iPlayer.hp;

	rEnemy.atk = rand() % 30 + 1;
	rEnemy.hp = rand() % 100 + 1;
	rEnemy.maxHp = rEnemy.hp;

	cout << "Succesfully randomized." << endl;

	cout << "Player's Health Points: " << iPlayer.hp << endl;
	cout << "Player's Attack points: " << iPlayer.atk << endl;
	cout << "Player's Magic points: " << iPlayer.mag << endl << endl;

	cout << "Enemy's Health Points: " << rEnemy.hp << endl;
	cout << "Enemy's Attack points: " << rEnemy.atk << endl;

	int selection;

	#ifndef __SWITCH__
	cout << "\nDo you want to:\n\t1-Continue\n\t2-Re-randomize\n\t3-Quit\n";
	cin >> selection;
	#else
	cout << "\nDo you want to:\n\tL-Continue\n\tR-Re-randomize\n\tZL-Quit\n";
	selection = getnum();
	#endif
	switch(selection)
	{
    case(1):
        Battle(rEnemy);
        Start();
        break;
    case(2):
        Randomize();
        break;
    case(3):
        Start();
        break;
    default:
        Start();
	}
}

void Engine::Magic(Enemy& enemy)
{
	cls();
	int selection = 1;
	#ifndef __SWITCH__
	cout << "Select a spell.\n\t1-Cure\n\t2-Fireball\n\t3-Exit\n";
	cin >> selection;
	#else
	cout << "Select a spell.\n\tL-Cure\n\tR-Fireball\n\tZL-Exit\n";
	selection = getnum();
	#endif
	switch (selection)
	{
	case(1):
		iPlayer.hp += iPlayer.mag;
		if (iPlayer.hp > iPlayer.maxHp)
			iPlayer.hp = iPlayer.maxHp;
		setColor(2);
		cout << iPlayer.name << " heals " << iPlayer.mag << " HP.\n";
		resetColor();
		getch();
		break;
	case(2):
		enemy.hp -= iPlayer.mag;
		setColor(4);
		cout << "The enemy takes " << iPlayer.mag << " of magical damage!\n\n";
		resetColor();
		getch();
		break;
	case(3):
		break;
	default:
		break;
	}
}

void Engine::Magic(Dummy& mDummy)
{
	cls();
	int selection = 1;
	#ifndef __SWITCH__
	cout << "Select a spell.\n\t1-Cure\n\t2-Fireball\n\t3-Exit\n";
	cin >> selection;
	#else
	cout << "Select a spell.\n\tL-Cure\n\tR-Fireball\n\tZL-Exit\n";
	selection = getnum();
	#endif
	switch (selection)
	{
	case(1):
		iPlayer.hp += iPlayer.mag;
		if (iPlayer.hp > iPlayer.maxHp)
			iPlayer.hp = iPlayer.maxHp;
		setColor(2);
		cout << iPlayer.name << " heals " << iPlayer.mag << " HP.\n";
		resetColor();
		getch();
		break;
	case(2):
		mDummy.hp -= iPlayer.mag;
		setColor(4);
		cout << "The dummy takes " << iPlayer.mag << " of magical damage!\n\n";
		resetColor();
		getch();
		break;
	case(3):
		break;
	default:
		break;
	}
}


void Engine::PlayerUp()
{
    iPlayer.hp = iPlayer.maxHp;
    iPlayer.level++;
    iPlayer.nextlevel = iPlayer.nextlevel *= 2;
    setColor(9);
    cout << iPlayer.name << " leveled up!\n\n";
    resetColor();
    if(iPlayer.level >= 2 && iPlayer.level <= 4)
    {
        iPlayer.hp += 5;
        iPlayer.atk += 2;
        iPlayer.mag += 5;
        iPlayer.maxHp = iPlayer.hp;
    }
    if(iPlayer.level >= 5 && iPlayer.level <= 9)
    {
        iPlayer.hp += 10;
        iPlayer.atk += 5;
        iPlayer.mag += 10;
        iPlayer.maxHp = iPlayer.hp;
    }
    if(iPlayer.level >= 10 && iPlayer.level <= 20)
    {
        iPlayer.hp += 15;
        iPlayer.atk += 10;
        iPlayer.mag += 15;
        iPlayer.maxHp = iPlayer.hp;
    }
    getch();
    Stats();
}

void Engine::Stats()
{
    cout << iPlayer.name << " " << iPlayer.surname << "'s statistics." << endl;
	cout << "\tClass: " << iPlayer.playerclass << endl;
	cout << "\tLevel: " << iPlayer.level << endl;
	cout << "\tExperience Points: " << iPlayer.exp << endl;
	cout << "\tExperience Points to the next level: " << iPlayer.nextlevel << endl;
	cout << "\tHealth Points: " << iPlayer.hp << endl;
	cout << "\tAttack points: " << iPlayer.atk << endl;
	cout << "\tMagic points: " << iPlayer.mag << endl;
	getch();
}

template <size_t rows, size_t columns>
void Engine::UpdateDungeon(string (&iDungeon)[rows][columns])
{
    cls();
    srand(time(NULL));
    int encounter = rand() % 4;
    iLocation.ShowMap(iDungeon);
    locate(iPlayer.x, iPlayer.y);
    cout << "P";
    char key = getch();
    switch (key)
    {
    case('a'):
	case('A'):
        if(iDungeon[iPlayer.x - 2][iPlayer.y - 1] == " ")
        {
            iPlayer.x--;
            if(encounter == 1)
                Battle(rEnemy);
        }
        break;
    case('s'):
	case('S'):
        if(iDungeon[iPlayer.x - 1][iPlayer.y] == " ")
        {
            iPlayer.y++;
            if(encounter == 1)
                Battle(rEnemy);
        }
        break;
    case('d'):
	case('D'):
        if(iDungeon[iPlayer.x][iPlayer.y - 1] == " ")
        {
            iPlayer.x++;
            if(encounter == 1)
                Battle(rEnemy);
        }
        break;
    case('w'):
	case('W'):
        if(iDungeon[iPlayer.x - 1][iPlayer.y - 2] == " ")
        {
            iPlayer.y--;
            if(encounter == 1)
                Battle(rEnemy);
        }
        break;
    case('q'):
    case('Q'):
        Pause();
        break;
    default:
        break;
    }
    cout.flush();
    UpdateDungeon(iDungeon);
}

void Engine::Pause()
{
    cls();
    int selection = 1;
    #ifndef __SWITCH__
    cout << "Pause Menu\n\n1-Return\n2-Save\n3-Main Menu\n4-Exit Game\n\n";
    cin >> selection;
    #else
    cout << "Pause Menu\n\nL-Return\nR-Save\n3ZL-Main Menu\nZR-Exit Game\n\n";
    selection = getnum();
    #endif
    switch(selection)
    {
    case(1):
        break;
    case(2):
        Save();
        break;
    case(3):
        Start();
        break;
    case(4):
        exit(0);
    default:
        Pause();
    }
}
