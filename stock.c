#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "stock.h"
#include <limits.h>
#include <float.h>



// func
//numStockItems = readStockItems(struct StockRecord storeStock, MAX_STOCK_ENTRIES, STOCK_FROM_STDIN);

void clearKeyboard (void)
{
	while (getchar() != "\n");
}

int checkIntInRange(int input,int min, int max)
{
    if(input < min || input > max)
	{
		return 0;
	}
	else
		return 1;
}

int checkDoubleInRange(double input, double min, double max)
{
	if (input < min || input > max)
	{
		return 0;
	}
	else
		return 1;
}

int readStockItems(struct StockRecord storeStock[], int size, int STOCK_FROM_STDIN)
{
	

	int i = 0;

	for (i = 0;i < size;i++)
	{
		scanf("%d,%d,%lf,%d,%29[^\n]%*c", &storeStock[i].stockAmount, &storeStock[i].Items.cat, &storeStock[i].Items.unit_Price, &storeStock[i].Items.byWeight, &storeStock[i].Items.name);
		storeStock[i].remainAmount = storeStock[i].stockAmount;

		int needInput = 1;
		while (needInput == 1)
		{
			if (storeStock[i].stockAmount == 0)
			{
				return i; //failed if use break here. break only one loop. There are 2 loops.
			}
			else if (checkIntInRange(storeStock[i].stockAmount, 1, INT_MAX) == 0)
			{
				printf("Invalid amount - Enter a number greater than 0: ");
				scanf("%d,%d,%f,%d,%29[^\n]%*c", &storeStock[i].stockAmount, &storeStock[i].Items.cat, &storeStock[i].Items.unit_Price, &storeStock[i].Items.byWeight, &storeStock[i].Items.name);
				storeStock[i].remainAmount = storeStock[i].stockAmount;
			}
			else if (checkIntInRange(storeStock[i].Items.cat, 1, 7) == 0)
			{
				printf("Invalid Category - Enter a number between 1 and 7: ");
				scanf("%d,%lf,%d,%29[^\n]%*c", &storeStock[i].Items.cat, &storeStock[i].Items.unit_Price, &storeStock[i].Items.byWeight, &storeStock[i].Items.name);
			}
			else if (checkIntInRange(storeStock[i].Items.byWeight, 0, 1) == 0)
			{
				printf("Invalid soldByWeight - Enter a number between 0 and 1: ");
				scanf("%d,%29[^\n]%*c", &storeStock[i].Items.byWeight, &storeStock[i].Items.name);
			}
			else
				needInput = 0;
		}
	}
	return i;
}


void centreText(int size, char ch, char title[])
{
	int len = strlen(title); // sizeof(title)=4 the size of pointer
	int i = 0;
	int j = 0;
	for (i=1;i<=size;i++)
	{
		if (i > (size - len) / 2 && i <= (size + len) / 2)
		{
			printf("%c", title[j]);
			j++;
		}
		else
		{
			printf("%c", ch);
		}
	}
}


void transCat(int cat, char wordCat[])
{
	if(cat==1)
	{
		strcpy(wordCat , "produce");
	}else if (cat == 2)
	{
		strcpy(wordCat, "bakery");  
	}
	else if (cat == 3)
	{
		strcpy(wordCat, "meat");
	}
	else if (cat == 4)
	{
		strcpy(wordCat, "dairy");
	}
	else if (cat == 5)
	{
		strcpy(wordCat, "baking");
	}
	else if (cat == 6)
	{
		strcpy(wordCat, "house wares");
	}
	else
		strcpy(wordCat, "miscellaneous");
	return;
}


//printStockReport(storeStock, numStockItems);
void printStockReport(struct StockRecord storesStock[], int size)
{
	int i = 0;
	printf("%4s%31s%16s%8s%10s", "ID", "Product", "Cateory", "Price", "Quantity\n");
	for(i=0;i<size;i++)
	{
		printf("%4d%31s", (i + 1), storesStock[i].Items.name);

		char wordCat[14] = { '0' };
		transCat(storesStock[i].Items.cat, wordCat);
		printf("%16s", wordCat);

		printf("%8.2lf%9d\n", storesStock[i].Items.unit_Price, storesStock[i].stockAmount);
	}
	
	return;
}

int readSale(struct StockRecord storeStock[], int size, struct SalesRecord saleItems[])
{
	int i = 0;
	int cnt = 0;


	for(i=0; i<size;i++)
	{
		int needInput = 1;
		printf("Enter a product ID to purchase, and the quantity (0 to stop): ");

		while (needInput == 1)
		{
			scanf("%d,%lf", &i, &saleItems[i - 1].soldAmount);
			clearKeyboard;
						
			if (i == 0)
			{
				return cnt;
			}
			else if (checkIntInRange(i, 0, size) == 0)
			{
				printf("Invalid Product - Enter a number between 0 and %d:  ", size);
			}
			else if (checkDoubleInRange(saleItems[i - 1].soldAmount, 0, 100) == 0)
			{
				printf("Invalid quantity - Enter a number between 0.10 and 100.00: ");
			}
			else if (checkDoubleInRange(saleItems[i - 1].soldAmount, 0, storeStock[i - 1].remainAmount) == 0)
			{
				saleItems[i - 1].soldAmount = storeStock[i - 1].remainAmount;
				saleItems[i - 1].soldTotal += saleItems[i - 1].soldAmount;
				storeStock[i - 1].remainAmount -= saleItems[i - 1].soldAmount;
				needInput = 0;
				cnt++;
			}
			else
			{
				saleItems[i - 1].soldTotal += saleItems[i - 1].soldAmount;
				storeStock[i - 1].remainAmount -= saleItems[i - 1].soldAmount;
				needInput = 0;
				cnt++;
			}
		}
	}
	return cnt;
}

double printSalesReport(struct StockRecord storeStock[], struct SalesRecord saleItems[], int size)
{
	printf("\n");
	centreText(70, '*', " Seneca Groceries ");
	printf("\n");
 	centreText(70, '=', "");
	printf("\n");

	int i = 0;
	double amt = 0;
	double tax = 0;
	double total = 0;

	for (i = 0;i < size && (saleItems[i].soldAmount != 0); i++)
	{
		if (saleItems[i].Items.cat == 6 || saleItems[i].Items.cat == 7)
		{
			printf("%30s%9.2lf%8.2lf\n", saleItems[i].Items.name, saleItems[i].Items.unit_Price, saleItems[i].soldAmount * saleItems[i].Items.unit_Price);
			amt += saleItems[i].soldAmount * saleItems[i].Items.unit_Price;
			tax += (saleItems[i].soldAmount * saleItems[i].Items.unit_Price) * 0.13;
			total += (amt + tax);
		}
		else
		{
			printf("%30s%9.2lf%8.2lf\n", saleItems[i].Items.name, saleItems[i].Items.unit_Price, saleItems[i].soldAmount * saleItems[i].Items.unit_Price);
			amt += saleItems[i].soldAmount * saleItems[i].Items.unit_Price;
			total += (amt + tax);
		}
	}

	printf("%39s%8.2lf\n", "Purchase Total", amt);
	printf("%39s%8.2lf\n", "Tax", tax);
	printf("%39s%8.2lf\n", "Total", total);
	printf("Thank you for shopping at Seneca!\n");

	return total;
	
}





//printStockReport(storeStock, numStockItems);





//getTopSellers(storeStock, numStockItems, topSellers, 3, cat);





//printTopSellers(storeStock, topSellers, 3, cat);