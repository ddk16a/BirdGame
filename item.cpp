#include <iostream>
#include <cstddef>
#include "item.h"
#include "player.h"
using namespace std;

void Item::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	Game::print((bird->getNick() == "" ? "Your <" + bird->getName() : "<" + bird->getNick()) + "> looks somewhat angry but nothing happened.");
}

Item* Factory::gimme(std::string n, std::string nar)
{
	if (n == "MusicDoor")
		return new MusicDoor(nar);
	if (n == "Hummingbird")
		return new Bird(nar, "<Hummingbird>s are small birds with long beaks and very fast wings. They're fond of flower nectar, tree sap, and the occasional insect which they catch with their long pointy beak. Funny enough, this one's beak looks like a lock pick.", "<Hummingbird>", 1, "You've nabbed a <Hummingbird>.", true, KEY);
	if (n == "Songbird")
		return new Bird(nar, "<Songbirds> come in many different forms. They're a special classification of perching birds known for their excessive singing. They're quite entertaining for the first 5 minutes or so.", "<Songbird>", 3, "Congratulations, you now have a <Songbird> in your bag.", true, MUSIC);	
	if (n == "Pigeon")
		return new Bird(nar, "You should probably already know what a <pigeon> is, but they're smaller birds that enjoy hanging out with their flock and eating a wide variety of seeds, insects, and vegetation. They're not good for much besides friendship.", "<Pigeon>", 5, "You have bagged a <pigeon>.", true, NONE);
	if (n == "Murder")
		return new Bird(nar, "A <murder> of crows is like a singular crow, but there are in fact several of them. Some might call them a flock, but other (more informed) people call them a <murder>. Alternately, they can be called a horde (also cool), a hover (okay), a muster (eh), or a parcel (lame).", "<Murder>", 25, "You have successfully placed a whole bunch of birds in your bag. I wonder what these could be used for...", true, WEAPON);
	if (n == "Duck")
		return new Bird(nar, "This particular <duck> looks like a Mallard. He's a curious little guy who seems to enjoy picking up everything he sees in his beak. Could be helpful. This is a hint.", "<Duck>", 10, "You've made a new <duck> friend.", true, NONE);
	if (n == "Eagle")
		return new Bird(nar, "The <Eagle> has long, powerful claws useful for catching and ripping into prey (among other things). It's definitely a useful bird to keep in your bag.", "<Eagle>", 20, "You managed to shove a fully grown <eagle> into your bag without dying.", true, LOOT);
    if (n == "Hay")
		return new Item(nar,"There doesn't seem to be anything under the <hay>.","<Hay>",false);
    if (n == "Hammer")
		return new Item(nar,"The <hammer> is glued to the floor.","<Hammer>",false);
    if (n == "Photograph")
		return new Item(nar,"The <photograph> has an old woman with some pigeons sitting at a park bench on it.","<Photograph>",false);
    if (n == "Lamp")
		return new Item(nar,"The <lamp> must have been used recently, but who else could have been here?","<Lamp>",false);
	if (n == "HummingChest")
		return new HummingChest(nar);
	if (n == "SeedChest")
		return new SeedChest(nar);
	if (n == "Cage")
		return new Item(nar,"It's just an ordinary bird <cage>.","<Cage>",false);
	if (n == "Woodpecker")
		return new Bird(nar, "It's a small-ish <woodpecker>, but an annoying one. It keeps jumping up and down in the bag pecking at the sides. It's almost as if it doesn't even want to be kept in a cloth sack.", "<Woodpecker>", 10, "Congrats on your new woodpecker.", true, GLASS);
	if (n == "Tree")
		return new Item(nar,"This <tree> seems to have been here long before the house itself.","<Tree>",false);
	if (n == "Gate")
		return new Item(nar,"The <gate> somehow seems connected to the pipe flowing to the fountain.","<Gate>",false);
	if (n == "Door")
		return new Door(nar);
	if (n == "Fountain")
		return new Item(nar,"The <fountain> might have once been a beautiful addition to the courtyard, but now it spews disgusting water in all directions.","<Fountain>",false);
	if (n == "Pipe")
		return new Pipe(nar);
	if (n == "Gertrude")
		return new Gertrude(nar);
	
	return new Item(nar + " - THIS IS A DUMMY ITEM. THAT ISN'T SUPPOSED TO HAPPEN.","What a dumb item.","<DummyItem>",false);
}

void Bird::inspect() const
{
	cout << endl;
	Game::print("<" + (nick == "" ? name + ">" : nick + "> the <" + name + ">"));
	Game::print("^" + description);
}

void MusicDoor::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == MUSIC){
		Player::getPlayer()->getLocation()->unlock("Right");
		Game::print("The <door> glows with a bright golden light and it slowly slides open.");
		return;
	}
	
	Game::print("The <door> doesn't seem to move at all.");
}

void Door::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == GLASS ){
		Player::getPlayer()->getLocation()->unlock("Forward");
		Game::print("The window shatters and you're now able to crawl <forward> through the gap.");
		return;
	}else if(bird->getUse() == KEY ){
		Player::getPlayer()->getLocation()->unlock("Forward");
		Game::print("The door unlocks with a click.");
		return;
	}

	Game::print("The <door> doesn't seem to move at all.");
}

void Pipe::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == LOOT){
		Player::getPlayer()->getLocation()->unlock("Forward");
		Game::print("The eagle breaks the old, rusty pipe with ease and the water stops flowing. You hear the gate make a distinct noise.");
		return;
	}
	
	Game::print("There isn't much that bird can do against a metal pipe.");
}

void HummingChest::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == KEY){
		loot = new Bird("You never picked up the <hummingbird> from the chest.", "<Hummingbird>s are small birds with long beaks and very fast wings. They're fond of flower nectar, tree sap, and the occasional insect which they catch with their long pointy beak. Funny enough, this one's beak looks like a lock pick.", "<Hummingbird>", 1, "You've nabbed another <Hummingbird>.", true, KEY);
		Player::getPlayer()->getLocation()->addItem(loot);
		Game::print("With the lock picked, the <chest> opens up and you see a <hummingbird> inside.");
		return;
	}
	
	Game::print("That bird can't open a chest.");
}

void SeedChest::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == KEY){
		loot = new Item("You never picked up the <birdseed> from the chest.","It doesn't look like real birdseed. Oh well.","<Birdseed>",false);	
		Player::getPlayer()->getLocation()->addItem(loot);
		Game::print("With the lock picked, the <chest> opens up and you see a bag of <birdseed> inside.");
		return;
	}
	
	Game::print("That bird can't open a chest.");
}

void Gertrude::use(Item* b)
{
	Bird* bird =  static_cast<Bird*>(b);
	
	if(bird->getUse() == WEAPON){
		Game::print("GERTRUDE FRICKIN DIES.");
		return;
	}
	
	Game::print("<Gertrude> laughs and swats your bird aside. \"You can't harm me with such feeble birds!\"");
}

bool operator==(Item* i, std::string s) { 
	return i->getName() == "<" + s + ">" ;
}

bool operator==(Bird* b, std::string s) {
	return b->getName() == "<" + s + ">" || b->getNick() == "<" + s + ">";
}
