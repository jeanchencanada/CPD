#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>


#define MAX_STOCK_ENTRIES 100
#define MAX_ITEMS_IN_SALE 100
#define NUM_CATS 7

//struct

struct ItemInfo
{
	char name[30];
	int cat;
	double unit_Price;
	int byWeight;
};


struct StockRecord
{
	struct ItemInfo Items;
	int stockAmount;
	double remainAmount;
};

struct SalesRecord 
{
	struct ItemInfo Items;
	double soldAmount;
	double soldTotal;
};



// func

void clearKeyboard(void);

void getItem(struct ItemInfo Items[]);


int readStockItems(struct StockRecord storeStock[], int size, int STOCK_FROM_STDIN);


void centreText(int size, char ch, char title[]);

void transCat(int cat);


//int readStockItems(struct StockRecord storeStock, MAX_STOCK_ENTRIES, STOCK_FROM_STDIN);
//
//centreText(70, '*', " Seneca Groceries - Opening Stock ");
//
//printStockReport(storeStock, numStockItems);
//
//numSaleItems = readSale(storeStock, numStockItems, saleItems);
//
//sale = printSalesReport(storeStock, saleItems, numSaleItems);
//
//printStockReport(storeStock, numStockItems);
//
//getTopSellers(storeStock, numStockItems, topSellers, 3, cat);
//
//
//printTopSellers(storeStock, topSellers, 3, cat);

