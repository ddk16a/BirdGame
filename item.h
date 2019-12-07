#ifndef ITEM_H
#define ITEM_H

	#include <iostream>
	#include <cstddef>
	#include "game.h"
	
	enum Equipment {KEY, WEAPON, MUSIC, LOOT, GLASS, NONE};

	class Item
	{
		public:
			Item(std::string nar, std::string des, std::string n, bool g) : narration(nar), description(des), name(n), gatherable(g), equipment(NONE) {}
			virtual ~Item() {};
			
			virtual void use(Item* bird);
			virtual void inspect() const { Game::print(description); }
			
			std::string getDescription() const { return description; }
			std::string getName() const { return name; }
			void getNarration() const { Game::print(narration); }
			
			bool getGather() const { return gatherable; }
			
			std::string narration;
			std::string description;
			std::string name;
			bool gatherable;
			Equipment equipment;
	};
	

	bool operator==(Item*, std::string);

	class Factory
	{
	    public:
	        static Item* gimme(std::string n, std::string nar);
	};

	class Creature : public Item
	{
		public:
			Creature(std::string nar, std::string des, std::string n, bool g) : Item(nar,des,n,g), alive(true)  {}
			virtual ~Creature() {}
			
			virtual void inspect() const { Game::print("This creature hasn't yet been configured for interaction."); };
			virtual Equipment getUse() const { return NONE; }
			
		protected:
			bool alive;
	};

	class Bird : public Creature
	{
		public:
			Bird(std::string nar, std::string des, std::string n, int dur, std::string gText, bool g, Equipment eq) : Creature(nar,des,n,g), nick(""), durability(dur), maxDurability(dur), gatherText(gText), equipment(eq) {}
			virtual ~Bird() {}

			void setNick(std::string n) { nick = "<" + n + ">"; }
			std::string getNick() { return nick; }
			
			Equipment getUse() const { return equipment; }
			int getDurability() const { return durability; }
			void changeDurability(int x) { durability += x; }
			
			std::string getGather() const { return gatherText; }
			std::string getListing() const { return (nick == "" ? "<" + name + ">" : "<" + nick + "> the <" + name + ">"); }
			
			void inspect() const;

		private:
			std::string nick;
			int durability;
			int maxDurability;
			std::string gatherText;	
			Equipment equipment;
	};

	bool operator==(Bird*, std::string);

	class MusicDoor : public Item
	{
		public:
			MusicDoor(std::string nar) : Item(nar,"As you look more closely, you see a faint glow around the edges whenever you make a noise.","<Door>",false) {}
			virtual ~MusicDoor() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
	};
	
	class Door : public Item
	{
		public:
			Door(std::string nar) : Item(nar,"The door it locked, but the windows above may be large enough to crawl through. If only you had something to break the glass.","<Door>",false) {}
			virtual ~Door() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
	};
	
	class Pipe : public Item
	{
		public:
			Pipe(std::string nar) : Item(nar,"I wonder what logically unrelated item might be affected and cause the plot to move forward if this pipe is somehow broken...","<Pipe>",false) {}
			virtual ~Pipe() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
	};
	
	class HummingChest : public Item
	{
		public:
			HummingChest(std::string nar) : Item(nar,"This <chest> looks fairly new. It can't have been locked long.","<Chest>",false) {}
			virtual ~HummingChest() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
			
		private:
			Item* loot;
	};
	
	class SeedChest : public Item
	{
		public:
			SeedChest(std::string nar) : Item(nar,"It's inevitable some valuable item will be hidden in here.","<Chest>",false) {}
			virtual ~SeedChest() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
			
		private:
			Item* loot;
	};
	
	class Gertrude : public Item
	{
		public:
			Gertrude(std::string nar) : Item(nar,"What a rude old lady. If only you had some way to defend yourself.","<Gertrude>",false) {}
			virtual ~Gertrude() {};
			
			void use(Item* bird);
			void inspect() const { Game::print(description); }
	};
	
#endif
