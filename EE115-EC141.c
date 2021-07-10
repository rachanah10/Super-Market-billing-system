#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//stores product details
struct prod
{
	long int no;
	char name[10];
	float price;
	int q;
};

//stores discounts on products
struct disco
{
	long int no;
	float r;
};

//generates bill in file bill.dat
float billg()
{	
	FILE *fp, *str;
	char s;
	system("clear");
	struct prod p,a;
	long int f;
	str=fopen("bill.dat","w");
	fp=fopen("prod.dat","r");
	getchar();
	printf("GENERATING BILL:...");
	do
	{	
		printf("\n\n");
		fseek(fp,0,0);
		float tot=0;
		printf("ENTER ITEM CODE: ");
		scanf("%ld",&f);
		while(fread(&a, sizeof(struct prod), 1, fp))
		{
			if(f==a.no)
				break;
		}
		printf("\nITEM NAME: %s\n",a.name);
		printf("\nITEM PRICE: %f\n",a.price);
		printf("ENTER QUANTITY: ");
		scanf("%d",&a.q);
		tot=tot+(a.q*a.price);
		fwrite (&a, sizeof(struct prod), 1, str);
		printf("\nTOTAL: %f\n\n",tot);
		getchar();
		printf("CHECK OUT (y/n)");
		scanf("%c",&s);
	}while(s!='y');
	fclose(str);
	fclose(fp);
	float tot=0;

	//checks for discount
	struct disco di;
	str=fopen("bill.dat","r");
	system("clear");
	printf("\n\n**************\tTOTAL BILL\t*******************");
	while(fread(&p, sizeof(struct prod), 1, str))
	{
		printf("\n\nIT code:%ld\n",p.no);
		printf("IT NAME:%10s\tPRICE:%f\tqANTITY:%d\n",p.name,p.price,p.q);
		fp=fopen("disco.dat","r");
		while(fread(&di, sizeof(struct disco), 1, fp))
		{
			if(di.no==p.no)
			{
				break;
			}
		}
		float k=(p.q*p.price*di.r)/100;
		printf("SuB Tot:%f\n\n",(p.q*p.price)-k);
		tot+=(p.q*p.price)-k;
	}
	printf("\n\n\n~~~~~~~~~~~~~~~~TOTAL: %f",tot);
	fclose(str);
	fclose(fp);
	return tot;
}

//function to add product to binary file, prod.dat
void addprod()
{
	FILE *str;
	str=fopen("prod.dat","a");
	struct prod p;
	getchar();
	printf("ENTER:\nITEM NUMBER: ");
	scanf("%ld",&p.no);
	getchar();
	printf("ITEM NAME: ");
	fgets(p.name, 10, stdin);
	printf("PRICE: ");
	scanf("%f",&p.price);
	p.q=0;
	fwrite (&p, sizeof(struct prod), 1, str);
	fclose(str);
}

//function to update discount on products
void adddis()
{
	system("clear"); 
	FILE *str;
	str=fopen("disco.dat","a");
	struct disco di;
	printf("ENTER:\nITEM NUMBER: "); 
	scanf("%ld",&di.no);
	printf("DISCOUNT: ");
	scanf("%f",&di.r);
	fwrite (&di, sizeof(struct disco), 1, str);
	fclose(str);
}

//main driver function
void main()
{
	char c;
	do
	{
		int n=0;
		printf("\n\n******************************MAIN MENU**********************\n");
		printf("\n\n1. GENERATE BILL");
		printf("\n\n2. ADD PRODUCT\n\n3. VIEW PRODUCT LIST\n\n4. ADD DISCOUNT\n\n5. VIEW DISCOUNT LIST");
		printf("\n\n*************************************************************\n");
		printf("ENTER an option:  ");
		scanf("%d",&n);
		//generates bill
		if(n==1)
		{
			do
			{
				float tot=billg();
				float payed, change;
				printf("AMT. paid:  ");
				scanf("%f",&payed);
				change=payed-tot;
				if(change<0)
					printf("ERROR: payment incomplete\n");
				else if(change==0)
					printf("****PAYMENT DONE******\n");
				else
					printf("****Change:  %f\n",change);
				printf("**********Have a nice Day!!***********\n");
				getchar();
				printf("NEW BILL?(y/n)");
				scanf("%c", &c);
			}while(c=='y');
		}

		//adds product to prod.dat
		else if(n==2)
		{
			int i;
			printf("ENTER THE NUMBER OF PRODUCTS TO BE ADDED:  ");
			scanf("%d", &i);
			while(i>0)
			{
				i--;
				addprod();
			}
			printf("PRODUCT DETAILS ADDED TO THE DATABASE\n");
		}

		//adds discounts to disco.dat
		else if(n==4)
		{
			int i;
			printf("ENTER THE NUMBER OF DISCOUNTS TO BE UPLOADED:  ");
			scanf("%d",&i);
			while(i>0)
			{
				i--;
				adddis();
			}
			printf("DISCOUNTED RATES HAVE BEEN UPLOADED\n");
		}

		//lists out the existing product list
		else if(n==3)
		{
			FILE *str;
			str=fopen("prod.dat","r");
			struct prod p;
			getchar();
			while(fread(&p, sizeof(struct prod), 1, str))
			{
				printf("\nITEM NUMBER: %ld\n",p.no);
				printf("ITEM NAME: %s\n",p.name);
				printf("PRICE: %f\n\n",p.price);
			}
			fclose(str);
		}
		//lists out existing discounts on products
		else if(n==5)
		{
			FILE *str;
			str=fopen("disco.dat","r");
			struct disco di;
			getchar();
			while(fread(&di, sizeof(struct disco),1, str))
			{
				printf("\nITEM NUMBER: %ld\n",di.no);
				FILE *fp;
				fp=fopen("prod.dat","r");
				struct prod p;
				while(fread(&p, sizeof(struct prod), 1, fp))
				{
					if(p.no==di.no){
						printf("ITEM NAME: %s\n",p.name);
						printf("PRICE: %f\n",p.price);
					}
					
				}
				fclose(fp);
				printf("DISCOUNT RATE: %f\n",di.r);
			}
			fclose(str);
		}

		else
			printf("ENTER a VALID OPTION\n");
		getchar();
		printf("Do you want to return to the MAIN MENU?(y/n)");
		scanf("%c",&c);
	}while(c=='y');
	
}
