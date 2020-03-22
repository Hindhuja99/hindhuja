// Bus Reservation System
/* A project on  Real Time Applications in C
   Done by
   HINDHUJA K,
   111716107016,
   EIE-A,
   R.M.k. Engineering College.
   COE- Automotive Elecronics.
   DATE:24.01.18  */


#include<stdio.h>
#include<string.h>

int n;
int c = 1, t[10][10];
static int sa1 = 10, sa2 = 20;
int Totalcost;

void enquiry();
int initialdetails();
void booking(int y);
void details();
void chooseseats();
void seater();
void semisleeper();

int e, a[20], ch, y, m, n1, u, date, year, ti, count = 0;
char month[100];
int p, q, b, i, d, b1;
struct book
{
	char gender[100];//Enter m for MALE,f for FEMALE,t for OTHERS
	char name[100];
	int age;

}s[20];


void enquiry() {
	printf("\n\nEnter the corresponding number of bus to get the details");
	scanf("%d", &d);
	// kindly enter the valid option
	switch (d)
	{

	case 1:
	{
		printf("\n 2+1 SLEEPER ( FROM: Chennai  TO: Bangalore)");
		printf("\n Total Seats: 10");
		printf("\n Available seats are:%d", sa1);
		printf("\n No.of Buses on this type: 10");
		printf("\n Timings: 7 pm, 8 pm, 9 pm");
		printf("\n Stoppings: vellore,Thiruvanamalai");
		printf("\n cost of tickets:\n");
		printf("\n        From chennai to vellore: Rs.200 per ticket\n");
		printf("\n        From chennai to Thiruvanamalai: Rs. 300 per ticket\n");
		break;
	}
	case 2:
	{
		printf("\n 2+1 SEMISLEEPER ( FROM: Chennai  TO: Theni)");
		printf("\n Total Seats: 20");
		printf("\n Available seats:%d", sa2);
		printf("\n No.of Buses on this type: 10");
		printf("\n Timings: 7 pm, 9 pm, 10 pm");
		printf("\n Stoppings: periyakulam,vathalagundu");
		printf("\n cost of tickets:");
		printf("\n          From chennai to vanthalagundu: Rs.200 (seater),Rs. 400(sleeper) per ticket \n");
		printf("\n          From chennai to periyakulam: Rs. 300(seater),Rs.500(sleeper) per ticket\n");
		break;
	}
	default:
	{

		break;

	}

	}
}
void seater()//to get the cost of the tickets
{
	int p;
	int q;
	printf("\n\n       A  From chennai to vellore: Rs.200 per ticket\n");
	printf("\n       B  From chennai to Thiruvanamalai: Rs. 300 per ticket\n");
	printf("\n1.  %d seats are in  A route", n);
	printf("\n2.  %d seats are in  B route", n);
	printf("\n3.  %d seats are in  A & B route", n);
	printf("\nEnter the format of booking(1-3)");
	scanf("%d", &b);
	switch (b)
	{
	case 1:
	{
		Totalcost = (n * 200);
		break;
	}

	case 2:
	{
		Totalcost = (n * 300);
		break;
	}
	case 3:
	{
		printf("\n Enter the number for A route");
		scanf("%d", &p);

		printf("\n Enter the number for B route");
		scanf("%d", &q);

		Totalcost = ((p * 200) + (q * 300));
		break;
	}
	default:
	{break;}
	}
}

void semisleeper()
{
	int p1;
	int q1;

	printf("\n\n          A   From chennai to Theni: Rs.200 (seater) per ticket\n");
	printf("\n            B   From chennai to Theni: Rs. 400(sleeper) per ticket \n");// payments may differ for various stoppings


	printf("\n1.  %d seats are in  A route", n);
	printf("\n2.  %d seats are in  B route", n);

	printf("\n3.  %d seats are in  A & B route", n);
	printf("\nEnter the format of booking(1-3)");
	scanf("%d", &b1);
	// kindly enter the valid option
	switch (b1)
	{
	case 1:
	{
		Totalcost = (n * 200);
		break;
	}

	case 2:
	{
		Totalcost = (n * 400);
		break;
	}
	case 3:
	{
		printf("\n Enter the number for A route");
		scanf("%d", &p1);

		printf("\n Enter the number for B route");
		scanf("%d", &q1);

		Totalcost = ((p1 * 200) + (q1 * 400));
		break;
	}
	default:
	{break;}
	}
}

int initialdetails()   // get the details from the user for booking
{
	int y1;
	printf("\n\n\n Please don't give the details for children less than 6 ");
	printf("\n How many persons are travelling ?\n");
	scanf("%d", &n);
	printf("\n\n Enter the date, Month,year like 1Feb1998\n");//enter a valid number
	scanf("%d%s%d", &date, month, &year);
	printf("\n\n 1. SEATER\n");
	printf("\n 2. SEMISLEEPER/n");
	printf("\nEnter the bus (1 or 2) that you want to book with\n");
	scanf("%d", &y1);
	switch (y1)
	{
	case 1:
	{
		printf("\nseats available are : %d", sa1);

		printf("\nvalid timings are: 7pm,8pm,9pm\n");
		printf("\nprefer your time:\n");      sa1 -= n;
		scanf("%d", &ti);
		break;
	}
	case 2:
	{
		printf("\nseats available are: %d", sa2);
		printf("\nvalid timings are: 7pm,10pm,9pm\n");
		printf("\nprefer your time:\n");        sa2 -= n;
		scanf("%d", &ti);
		break;
	}
	default:
	{
		printf("Enter a valid option");// kindly enter the valid option alone
		break;

	}
	}

	for (i = 0;i < n;i++)
	{
		printf("\nEnter the name of the %d person", i + 1);// enter the name without space
		scanf("%s", s[i].name);
		printf("\nEnter the age of the %d person", i + 1);
		scanf("%d", &s[i].age);
		printf("\nEnter the gender of the %d person\n", i + 1);
		scanf("%s", s[i].gender); // m or f or t ,single characters
	}
	return y1;
}

void booking(int y)
{
	//The no. of the bus (1 or 2) to book with,

	if (y == 1)
	{
		seater();
	}
	if (y == 2)
	{
		semisleeper();
	}
}



void chooseseats() {
	int j, k, u;
	printf("\nThe booked numbers are indicated by 0\n");
	for (j = 0;j < 3;j++)
	{
		for (k = 0;k < 3;k++)
		{
			if (k == 1)
				printf(" ");

			printf("%d\t", t[j][k]);
		}
		printf("\n");
	}
	// choose seat numbers
	printf(" Enter the seat numbers for your wish");// the seat numbers are to be entered according to the available seats
	for (u = 0;u < n;u++)
	{
		scanf("%d", &a[u]);
	}
	u = 0;
	for (m = 0;m < 3;m++)
		for (n1 = 0;n1 < 3;n1++)
		{
			if (t[m][n1] == a[u] && t[m][n1] != 0)
			{
				t[m][n1] = 0;

				u++;
			}
		}
}
void details() {
	printf("\n\n\n       INVOICE ");
	printf("\n\nDate : %d:%s:%d", date, month, year);

	for (i = 0;i < n;i++)
	{
		printf(" Name: %s       ", s[i].name);
		printf(" Age: %d        ", s[i].age);
		printf(" Gender: %s\n ", s[i].gender);
	}
	printf("\nThe Total cost of your Ticket(s): %d", Totalcost);     // print the final receipt here
	printf("\nThe Seat numbers that you have booked");
	for (i = 0;i < n;i++)
	{
		printf("%d\t", a[i]);
	}

}


void main()
{

	if (count < 1)
	{
		for (m = 0;m < 3;m++)
		{
			for (n1 = 0;n1 < 3;n1++)
			{

				t[m][n1] = c;c++;

			}

		} count++;
	}
label1:
	{

		printf("                        Welcome to Our ABC services\n\n\n");
		printf("\n The Buses that we are Currently Running are:");
		printf("\n   1.   2+1 SEATER ( FROM: Chennai  TO: Bangalore)");     // N numnber of buses can be added in this list
		printf("\n   2.   2+1 SEMISLEEPER ( FROM:Chennai TO:Theni)\n");
		printf(" \n 1. If you want to know the details before booking ,enter choice as 1");    //  Know the purpose of the user
		printf(" \n 2. If you want to book then,enter the choice as 2");

		printf("\n Now, Enter your choice");
		scanf("%d", &e);

		switch (e)
		{
		case 1:
		{ enquiry();// The enquiry block
		break;
		}
		case 2:
		{
			enquiry();
			y = initialdetails();//The enquiry and booking both are done
			booking(y);
			chooseseats();
			details();
			break;
		}



		default:
		{ printf(" enter a valid choice");

		}
		}
		printf("\nEnter the choice as 1 if you are going to exit the page");
		printf("\nEnter the choice as 2 if you want continue booking for the other buses");
		printf("\nEnter the choice");
		scanf("%d", &ch);
		// kindly enter the valid option

		switch (ch)

		{
		case 1:
		{
			printf("\nyou can pay the bill at the time of your Journey\n"); // The code for transaction can be written here
			printf("\n             Thanks for visiting us!!!\n");
			printf("\n                  HAPPY JOURNEY");
			break;
		}
		case 2:
		{ goto label1;//executes the next set of statements

		}
		default:
		{ break;}//kindly enter the valid number
		}
	}
}