// Fill out your copyright notice in the Description page of Project Settings.

#include "LSystem.h"
#include "StringBuilder.h"
LSystem::LSystem()
{
	sentence = "G";
	rules.push_back(Rule('F', "G[-F][+F][+*F][+/F]"));
	rules.push_back(Rule('G', "G[-F][+F][+*F][+/F]"));
	rules.push_back(Rule('F', "G[-F][+F][+*F]"));
	rules.push_back(Rule('G', "G[-F][+F][+*F]"));
	rules.push_back(Rule('F', "G[-F][+F][-/F]"));
	rules.push_back(Rule('G', "G[-F][+F][-/F]"));
	rules.push_back(Rule('F', "G[-F][-/F]"));
	rules.push_back(Rule('G', "G[-F][-/F]"));
	rules.push_back(Rule('F', "G[-F][+*F]"));
	rules.push_back(Rule('G', "G[-F][+*F]"));
	rules.push_back(Rule('G', "G"));
	rules.push_back(Rule('F', "G"));
	rules.push_back(Rule('S', "S"));
	rules.push_back(Rule('D', "D"));
	
	generation = 0;
}
void LSystem::setType(string tag)
{
	if (tag == "tree")
	{
		sentence = "SG";
	}
	else
	{
		sentence = "G";
	}

	generation = 0;
}

LSystem::LSystem(string axiom, Rule rules[6])
{
	sentence = axiom;
	generation = 0;
}
string LSystem::rulePicker(char x)
{
	int count = 0;
	std::vector<int> index;
	for (int i = 0; i < rules.size(); i++)
	{
		if (x == rules.at(i).getA())
		{
			count++;
			index.push_back(i);
		}
	}
	if (count == 1)
	{
		return rules.at(index.at(0)).getB();
	}
	else if (count > 1)
	{
		int selected_index = FMath::RandRange(0, count-1);
		return  rules.at(index.at(selected_index)).getB();
	}
	else
		return "";
}

void LSystem::generate()
{
	StringBuilder next;
		
		// For every character in the sentence
	for (int i = 0; i < sentence.length(); i++) 
	{
		// What is the character
		char curr = sentence.at(i);
		// We will replace it with itself unless it matches one of our rules
		string replace = rulePicker(curr);
		next.append(replace);
	}
	// Replace sentence
	sentence = next.str();
	// Increment generation
	generation++;
	
}
LSystem::~LSystem()
{
}
