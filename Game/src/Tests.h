#pragma once
#include "Player.h"
#include "iostream"

class testPlayer 
{
	testPlayer() {};

	void testTakeDamage() {
		Player p;
		bool success = false;
		
		p.takeDamage(10);

		if (success == true)
		{
			std::cout << "Function takeDamage successful" << std::endl;
		}
		else
		{
			std::cout << "Function takeDamage not successful" << std::endl;
		}
	};

	void testGetKey() {
		Player p;
		bool success = false;

		p.setKey(true);

		success = p.getKey();

		if (success == true)
		{
			std::cout << "Function getKey successful" << std::endl;
		}
		else
		{
			std::cout << "Function getKey not successful" << std::endl;
		}
	};
};