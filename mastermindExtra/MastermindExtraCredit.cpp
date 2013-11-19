// Sohom Bhattacharya
// Homework 3
// October 25, 2013


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;



int rollDie(int sides)
{
	srand(time(NULL));


	int roll = rand()%sides + 1;
	return roll;
}


int nthDigit(int &combination, int position)
{
	    int testComb = combination;
		int g_thousandsdigit;
		int g_hundredsdigit;
		int g_tensdigit;
		int g_onesdigit;
		int digits = 0;
		int position_value = 0;

		while (testComb != 0)
		{
			testComb /= 10;
			digits++;
		}

		if (position > 0 && digits == 4)
		{
			g_thousandsdigit = combination/1000;
							g_hundredsdigit = (combination - 1000*g_thousandsdigit)/100;
							g_tensdigit = (combination - (1000*g_thousandsdigit + 100*g_hundredsdigit))/10;
							g_onesdigit = combination - 1000*g_thousandsdigit - 100*g_hundredsdigit - 10*g_tensdigit;


		if (position == 3)
		position_value = (combination - 1000*g_thousandsdigit)/100;

		if (position == 2)
		position_value = (combination - (1000*g_thousandsdigit + 100*g_hundredsdigit))/10;


		if (position == 1)
		position_value = combination - 1000*g_thousandsdigit - 100*g_hundredsdigit - 10*g_tensdigit;


		if (position == 4)
		position_value = combination/1000;
		}
		return position_value;

}

void clearnthDigit(int &combination, int position)
{
			nthDigit(combination, position);
			int value; 
			if (position == 1)
				value = nthDigit(combination, position);
			if (position == 2)
				value = nthDigit(combination, position)*(pow(10,1));
			if (position == 3)
				value = nthDigit(combination,position)*(pow(10,2));
			if (position == 4)
				value = nthDigit(combination, position)*(pow(10,3));
			
			combination = combination - value;

			
}

void evaluate (int answer, int guess, int& black, int& white)
{
 black = 0;
 white = 0;
		int counter = 1;
		int counter2 = 1;
		int counter3 = 1;
		while (counter <= 4)
		{
			if (nthDigit(guess,counter) == nthDigit(answer,counter))
			{
				black++;
				clearnthDigit(answer,counter);
			}

			counter++;
		}

		while (counter3 <= 4)
		{ int counter4 = 1;
			while (counter4 <= 4)

			{
				if (nthDigit(guess,counter3) == nthDigit(answer,counter4))
				{
				white++;
				clearnthDigit(guess,counter3);
				}
				counter4++;
			}
			counter3++;
		}

		

}

int generateAnswer()
{
	int combination;
	int ones = rollDie(8);
	int tens = rollDie(8);
	int hundreds = rollDie(8);
	int thousands = rollDie(8);

	combination = 1000*thousands + 100*hundreds + 10*tens + ones;

	
	return combination;

}

void generateSearchSpace(int guesses[], int length)
{
			

		
	int h = 0; 
	{
	for (int i = 1; i <=8; i++)
	{
	for (int j = 1; j <=8; j++)
	{
	for (int k = 1; k <=8; k++)
	{
	for (int l = 1; l <=8; l++)
	{
	guesses[h] = 1000*i + 100*j + 10*k + l;
	h++;
	}
	}
	}
	}
	}

	
}


void trim(int guesses[], int& length, int guess, int black, int white)
{

	int counter = 0;
	int counter2 = 0; 
	int testBlack, testWhite;
	for (int i = 0; i < length; i++)
	{
		int answer = guesses[i];
		
		evaluate(answer,guess, testBlack, testWhite);

		if (testBlack == black && testWhite == white)
		{
			guesses[counter2] = guesses[i];
			counter2 = counter2 + 1;
		}


	}
			length = counter2;

	
}



void methodicalEliminate(int answer, int& Methodical_count)
{
	int counter = 0;
	int guesses [4906];
	int black = 0;
	int white = 0;
	int new_length = 4096;
	generateSearchSpace(guesses,4906);
	Methodical_count = 0;
	while (guesses[0] != answer)
	{
		counter = counter + 1;
		
		evaluate(answer, guesses[0], black, white);
		trim(guesses, new_length, guesses[0],black, white);
		

		

	}
	if (guesses[0] == answer)
		{counter = counter + 1;
		}
	Methodical_count = counter;

	
}

void guessAndEliminate(int answer, int& Guess_count)
{
int new_counter = 0;
Guess_count = 0;
int next_length = 4096;
int new_guesses[4096];
generateSearchSpace(new_guesses,4096);
int black = 0;
int white = 0;
int j = rand()%next_length + 1;  	

while (new_guesses[j] != answer)
	{
		
		new_counter = new_counter + 1;
		
		evaluate(answer, new_guesses[j], black, white);
		trim(new_guesses, next_length, new_guesses[j],black, white);
		j = rand()%next_length;  	

	}
	if (new_guesses[j] == answer)
		{new_counter = new_counter + 1;
		}

	Guess_count = new_counter;

}

void guessThreeandEliminate(int answer, int& Three_count)
{
	int third_counter = 0;
	Three_count = 0;
	int third_guesses [4096];
	int black = 0;
	int white = 0;
	int length = 4096;
	int third_new_length = 4096;
	generateSearchSpace(third_guesses,4906);
	int first;
	int second;
	int third;
	int i = 1;

	for (int j = 0; j < 3; j++)
	{
		third_counter = third_counter + 1;
		int i = rand()%third_new_length + 1;
		if (third_guesses[i] == answer)
		{
			third_counter = third_counter + 1;
		
		}
	if (j == 0) 
		first = i;
	if (j == 1)
		second = i;
	if (j == 2)
		third = i;
	}

	evaluate(answer, first, black, white);
	trim(third_guesses, third_new_length, first, black, white);

	evaluate(answer, second, black, white);
	trim(third_guesses, third_new_length, second, black, white);

	evaluate(answer, third, black, white);
	trim(third_guesses, third_new_length, third, black, white);

	i = rand()%third_new_length + 1;  

	while (third_guesses[i] != answer)
	{
		
		third_counter = third_counter + 1;
		
		evaluate(answer, third_guesses[i], black, white);
		trim(third_guesses, third_new_length, third_guesses[i],black, white);
		
		
		i = rand()%third_new_length;  	

		
	}
	if (third_guesses[i] == answer)
		{third_counter = third_counter + 1;
		}



	Three_count = third_counter; 


}


void playMastermind()
{

	string play_again = "yes";
	
	
	cout << "Enter yes to see the average number of guesses for each method" << endl;
	cin >> play_again;

	while (play_again == "yes")
	{
		int answer;					// answer value
		int first_count = 0;	    // counter of Methodical Eliminate
		int second_count = 0;		// counter of Guess and Eliminate
		int third_count = 0;		// counter of Guess Three and Eliminate
		int first_average = 0;		// average of all 100 counter values of Methodical Eliminate
		int second_average = 0;		// average of all 100 counter values of Guess and Eliminate 
		int third_average = 0;		// average of all 100 counter values of Guess Three and Eliminate
		int first_sum = 0;			// sum of all 100 counter values of Methodical Eliminate
		int second_sum = 0;			// sum of all 100 counter values of Guess and Eliminate
		int third_sum = 0;			// sum of all 100 counter values of Guess Three and Eliminate
		
		
		for (int i = 0; i < 99; i++)
		{
			cout << "Please wait..." << i << '\n';
			answer = generateAnswer();
			methodicalEliminate(answer, first_count);
			guessAndEliminate(answer, second_count);
			guessThreeandEliminate(answer, third_count);

			first_sum = first_sum + first_count; 
			second_sum = second_sum + second_count; 
			third_sum = third_sum + third_count;



			
		}

	
		
		first_average = first_sum/100;
		second_average = second_sum/100;
		third_average = third_sum/100;
	

		cout << "Methodical Eliminate required an average of " << first_average << " guesses" << '\n';
		cout << "Guess and Eliminate required an average of " << second_average << " guesses" << '\n';
		cout << "Guess Three and Eliminate required an average of " << third_average << " guesses" << '\n';
		cout << "Play again?" << endl;
		cin >> play_again;
	}

}



int main() {

	srand(time(NULL));

	playMastermind();
	


	



	return 0;
}




