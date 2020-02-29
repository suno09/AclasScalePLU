#ifndef PLU_H_INCLUDED
#define PLU_H_INCLUDED

typedef struct{
				char*	Name;
				long	LFCode;
				char*	Code;
				long	BarCode;
				long	UnitPrice;
				long	WeightUnit;
				long	Deptment;
				double	Tare;
				long	ShlefTime;
				long	PackageType;
				double	PackageWeight;
				long	Tolerance;
				char	Message1;
				char	Reserved;
				short	Reserved1;
				char	Message2;
				char	Reserved2;
				char	MultiLabel;
				char	Rebate;
				long	Account;
				}TPLU;
typedef TPLU* PPLU;
typedef TPLU TPLUCluster[4];
typedef TPLUCluster* PPLUCluster;
typedef long THotkeyTable[84];
typedef THotkeyTable* PHotkeyTable;

typedef int (CALLBACK* LPFNPBusConnect)(char *,char *,int,char *,int);
typedef int (CALLBACK* LPFNPBusDisConnect)(int);
typedef int (CALLBACK* LPFNPBusTransferPLUCluster)(PPLUCluster);
typedef int (CALLBACK* LPFNPBusTransferHotkey)(PHotkeyTable,int);
typedef int (CALLBACK* LPFNPBusPLUToStr)(PPLU,char *);
typedef int (CALLBACK* LPFNPBusStrToPLU)(char *,PPLU);

#endif // PLU_H_INCLUDED
