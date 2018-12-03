//Selin SEZER 17894


#include "Robots_Modified.h"
#include "miniFW_Modified.h"
#include "strutils.h"
#include "randgen.h"
#include <iostream>

using namespace std;

void DisplayYouWin(Robot& op1,Robot& op2, Robot& op3)
{
	int death1 = op1.GetDeaths();		// Helps to get death numbers 
	int death2 = op2.GetDeaths();
	int death3 = op3.GetDeaths();

	ShowMessage("You win! Opponent 1 died " +itoa(death1)+"times, opponent 2 died " +itoa(death2)+"times and opponent 3 died " +itoa(death3) + " times");
}
void DisplayThingCount(Robot& op1,Robot& op2, Robot& op3)
{
	int death1 = op1.GetDeaths();		// Helps to get death numbers 
	int death2 = op2.GetDeaths();
	int death3 = op3.GetDeaths();

	ShowMessage("You lost! Opponent 1 died " +itoa(death1)+"times, opponent 2 died " +itoa(death2)+"times and opponent 3 died " +itoa(death3) + " times");
}
void RandomTurn(Robot & f)						// Helps to make random turns
{
	RandGen gen;
	int num = gen.RandInt(1,5);
	for(int i=0;i<num;i++ )
		f.TurnRight();
		f.Move();
}

void RandomPutThings(Robot & f )
{
	RandGen gen;
	int nm1;
	nm1= gen.RandInt(1,10);
	for(int i=0; i<nm1; i++)
	{
		f.PutThing();
	}
}
void PickStuff (Robot & f )
{
	for(int i=0;i<100;i++)
		f.PickThing();
}

void RandomChoice(Robot & op1, Robot & op2, Robot & op3)
{
	RandGen gen;
	int num = gen.RandInt(1,3);
	if (num==1)
	{
		RandomTurn(op1);
		RandomPutThings(op1);
	}
	if (num==2)
	{
		RandomTurn(op2);		 
		RandomPutThings(op2);
	}
	if (num==3)
	{
		RandomTurn(op3);	
		RandomPutThings(op3);
	}
}	
void SuperRobot(Robot & r,Robot & op1,Robot & op2,Robot & op3)
{
	if (r.GetBagCount()>=50 && r.GetBagCount()<100 )
	{
		if (r.IsAlive()==false && (op1.IsAlive()==true && op2.IsAlive()==true && op3.IsAlive()==true))	// If robot dies and opponents still live, it means that robot faced a wall.
		{
			r.Resurrect();
			r.Teleport(6,6,east);
			r.SetBagCount(r);
			
			RandGen gen;
			int num = gen.RandInt(1,3);
			ShowMessage("Update" + itoa(num));
			if (num==1)
			{
				op1.SetOtherBagCount(op1);
				ShowMessage("old:"+ itoa(op1.GetBagCount()));
				ShowMessage("new:" + itoa(op1.GetBagCount()+10));
			}
			if (num==2)
			{
				op2.SetOtherBagCount(op2);
				ShowMessage("old:"+ itoa(op2.GetBagCount()));
				ShowMessage("new:" + itoa(op2.GetBagCount()+10));
			}
			if (num==3)
			{
				op3.SetOtherBagCount(op3);
				ShowMessage("old:"+ itoa(op3.GetBagCount()));
				ShowMessage("new:" + itoa(op3.GetBagCount()+10));
			}
		}
		if (r.IsAlive()==false && (op1.IsAlive()==false || op2.IsAlive()==false || op3.IsAlive()==false)) 
		{
			r.KillRobots();
		}
		
	}
	else if (r.GetBagCount()>100)		// If there are more than 100 things in bag it is an error, so player can't win.
		{
		r.KillRobots();
		DisplayThingCount(op1,op2,op3);
		} 
	else if (r.GetBagCount()==100)		// Robot will win if it take 100points.
	{
		DisplayYouWin(op1,op2,op3);
	}
}

void OpponentSaver(Robot & op1,Robot & op2,Robot & op3,Robot & r)
{	
	if (op1.IsAlive()==false && op2.IsAlive()!=false && op3.IsAlive()!=false && r.IsAlive()!=false)			
	// If anyone besides one opponent didn't died it means that opponent faced to wall.
	{
		op1.GetDeaths();
		op1.Resurrect();
		op1.Teleport(11,1,east);
	}
	if (op2.IsAlive()==false && op1.IsAlive()!=false && op3.IsAlive()!=false && r.IsAlive()!=false) 		
	{
		
		op2.GetDeaths();
		op2.Resurrect();
		op2.Teleport(1,11,east);
	}
	if (op3.IsAlive()==false && op2.IsAlive()!=false && op1.IsAlive()!=false && r.IsAlive()!=false) 		
	{
		op3.GetDeaths();
		op3.Resurrect();
		op3.Teleport(11,11,east);
	}
}

int main()
{
	int a,b,c;

	RandGen gen;
	a = gen.RandInt(1,98);
	b = gen.RandInt(1,98-a);
	c = 100-a-b;


	Robot r (0,0);						//player robot
	r.SetColor(red);

	Robot op1 (11,1, east, a);			//initial point(11,1)
	op1.SetColor(blue);

	Robot op2 (1,11,east, b);			//initial point(1,11)
	op2.SetColor(blue);

	Robot op3 (11,11, east, c);
	op3.SetColor(blue);
	
	while (r.IsAlive()== true && op1.IsAlive()== true && op2.IsAlive()== true && op3.IsAlive()== true)
	{
		if (IsPressed(keyRightArrow))
		{				
			r.Turn(east);
			r.Move();
			RandomChoice(op1,op2,op3);
			PickStuff(r);
			for (a=0; a<4; a++)
			{
			OpponentSaver(op1,op2,op3,r);
			}
			SuperRobot(r,op1,op2,op3);
			
		}
		else if (IsPressed(keyLeftArrow))
		{
			r.Turn(west);
			r.Move();
			RandomChoice(op1,op2,op3);
			PickStuff(r);
			for (a=0; a<4; a++)
			{
			OpponentSaver(op1,op2,op3,r);
			}
			SuperRobot(r,op1,op2,op3);

		}
		else if (IsPressed(keyUpArrow))
		{
			r.Turn(north);
			r.Move();
			RandomChoice(op1,op2,op3);
			PickStuff(r);
			for (a=0; a<4; a++)
			{
			OpponentSaver(op1,op2,op3,r);
			}
			SuperRobot(r,op1,op2,op3);
		}
		else if (IsPressed(keyDownArrow))
		{
			r.Turn(south);		
			r.Move();
			RandomChoice(op1,op2,op3);
			PickStuff(r);
			for (a=0; a<4; a++)
			{
			OpponentSaver(op1,op2,op3,r);
			}
			SuperRobot(r,op1,op2,op3);
		}
	}
	

	DisplayThingCount(op1,op2,op3);




	return 0;
}