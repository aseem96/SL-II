#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LS 10
#define MAX 200

typedef struct MDT{
	int sno;
	char str[LS][MAX];
	int instruct_count;
}MDT;

typedef struct MNT{
	int sno;
	char name[50];
	int pno;
	int kpno;
	int mdtp;
	int kptp;
	int ptp;
}MNT;

typedef struct PTAB{
	char pname[LS][MAX];
}PTAB;

typedef struct KPTAB{
	char kpname[LS][MAX];
	char value [LS][MAX];
}KPTAB;

typedef struct ALA{
	char name[LS][MAX];
	char value[LS][MAX];
}ALA;

void initialize(MDT mdt[LS],MNT mnt[LS])
{	int i;
	for(i=0;i<LS;i++)
	{
		mdt[i].sno=0;
		mdt[i].instruct_count=0;
		mnt[i].sno=0;
		mnt[i].pno=0;
		mnt[i].kpno=0;
	}
}

MDT mdt[LS];
MNT mnt[LS];
PTAB ptab[LS];
KPTAB kptab[LS];
int counter;

void macro_pass1()
{
	char s[MAX],s1[MAX],ch[LS],temp[MAX];
	char delim[]=" \n";
	char *token;
	int instruction_counter=0,i,macro_name_line=0,j,pcount=0,kpcount=0,pflag,k;

	initialize(mdt,mnt);

	FILE *fpr=fopen("input.txt","r");
	FILE *fpw=fopen("intermediate.txt","w");

	while(!feof(fpr))
	{
		fgets(s,MAX,fpr);
		strcpy(s1,s);
		token=strtok(s,delim);
		if(strcmp(token,"MACRO")!=0)
		{
			fputs(s1,fpw);
		}
		else
		{
			instruction_counter=0,macro_name_line=0,pcount=0,kpcount=0;
			fgets(s,MAX,fpr);
			strcpy(s1,s);
			token=strtok(s,delim);
			mdt[counter].sno=counter;
			while(strcmp(token,"MEND")!=0)
			{
				if(macro_name_line==0)
				{
					mnt[counter].sno=counter;
					strcpy(mnt[counter].name,token);

					token=strtok(NULL,delim);
					while(token!=NULL)
					{
						if(strstr(token,"=")!=NULL)
						{
							mnt[counter].kpno++;

							i=0;
							while(token[i++]!='=');
							k=i;
							j=0;
							if(token[i]=='\0')
							{
								strcpy(temp,"");
							}
							else
							{
								while(token[i]!='\0')
								{
									temp[j++]=token[i++];
								}
								temp[j]='\0';
								token[k]='\0';
							}
							strcpy(kptab[counter].kpname[kpcount],token);
							strcpy(kptab[counter].value[kpcount++],temp);
							strcpy(ptab[counter].pname[pcount++],token);
						}
						else
						{
							mnt[counter].pno++;
							strcpy(ptab[counter].pname[pcount++],token);
						}
						mnt[counter].mdtp=mdt[counter].sno;
						mnt[counter].kptp=counter;
						mnt[counter].ptp=counter;
						token=strtok(NULL,delim);
					}
					macro_name_line=1;
				}
				else
				{	strcpy(s1," ");
				while(token!=NULL)
				{
					pflag=0;
					for(i=0;i<pcount;i++)
					{
						if(strstr(ptab[counter].pname[i],token)!=NULL)
							pflag=1;
						if(strcmp(token,ptab[counter].pname[i])==0 || pflag==1)
						{
							ch[0]=i+48;
							ch[1]='\0';
							strcpy(token,ch);
							break;
						}
					}
					strcat(s1,token);
					strcat(s1," ");
					token=strtok(NULL,delim);
				}
				strcpy(mdt[counter].str[instruction_counter++],s1);
				}
				fgets(s,MAX,fpr);
				token=strtok(s,delim);
			}
			mdt[counter].instruct_count=instruction_counter;
			counter++;
		}
	}

	printf("\nMDT Details:\n");
	for(j=0;j<counter;j++)
	{	printf("#%d:\n",j+1);
	for(i=0;i<mdt[j].instruct_count;i++)
	{
		puts(mdt[j].str[i]);
	}
	}
	printf("\nMNT Details:\n");
	for(i=0;i<counter;i++)
	{
		printf("\nName:");
		puts(mnt[i].name);
		printf("SNO: #%d\t PNO: #%d\t KPNO: #%d\t MDTP: #%d\t",mnt[i].sno,mnt[i].pno,mnt[i].kpno,mnt[i].mdtp);
	}

	printf("\n\nPTAB Details:\n");
	for(i=0;i<counter;i++)
	{
		printf("\nPTAB for #%d:\n",i);
		for(j=0;j<(mnt[i].pno+mnt[i].kpno);j++)
		{
			printf("\nSno: #%d \t Name:%s\n",j,ptab[i].pname[j]);
		}
		printf("\n");
	}

	printf("\nKPTAB Details:\n");
	for(i=0;i<counter;i++)
	{
		printf("KTAB for #%d:\n",i);
		for(j=0;j<mnt[i].kpno;j++)
		{
			printf("\nSno: #%d \t Name:%s \tValue:%s\n",j,kptab[i].kpname[j],kptab[i].value[j]);
		}
		printf("\n");
	}
	fclose(fpr);
	fclose(fpw);
}

void macro_pass2()
{
	FILE *fpr=fopen("intermediate.txt","r");
	FILE *fpw=fopen("output.txt","w");

	ALA ala[LS];

	char s[MAX],delim[]=" \n",ch[MAX],s1[MAX],tempchar[9][2];
	char *token;
	int i,j,k,l,flag,temp_count,mdt_flag;

	fgets(s,MAX,fpr);
	strcpy(s1,s);

	while(!feof(fpr))
	{
		temp_count=0;
		flag=0;

		token=strtok(s,delim);

		for(i=0;i<counter;i++)
		{
			if(strcmp(mnt[i].name,token)==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			token=strtok(NULL,delim);
			while(token!=NULL)
			{
				if(strstr(token,"=")!=NULL)
				{
					j=0;
					while(token[j++]!='=');
					k=j;
					if(token[j]=='\0')
					{
						strcpy(ch,"");
					}
					else
					{
						l=0;
						while(token[j]!='\0')
						{
							ch[l++]=token[j++];
						}
						ch[l]='\0';
						token[k]='\0';
					}

					if(strstr(ptab[i].pname[temp_count],token)==NULL)
					{
						strcpy(ala[i].name[temp_count],ptab[i].pname[temp_count]);
						strcpy(ala[i].value[temp_count++],"");
						strcpy(ala[i].name[temp_count],token);
						strcpy(ala[i].value[temp_count],ch);
					}
					else
					{
						strcpy(ala[i].name[temp_count],token);
						strcpy(ala[i].value[temp_count],ch);
					}
				}
				else
				{
					strcpy(ala[i].name[temp_count],token);
					strcpy(ala[i].value[temp_count],"");
				}
				temp_count++;
				token=strtok(NULL,delim);
			}

			for(k=0;k<10;k++)
			{
				tempchar[k][0]=k+48;
				tempchar[k][1]='\0';
			}

			for(j=0;j<mdt[i].instruct_count;j++)
			{
				strcpy(s1,mdt[i].str[j]);
				strcpy(ch,"+");
				token=strtok(s1,delim);
				while(token!=NULL)
				{
					mdt_flag=0;
					for(k=0;k<mnt[i].pno+mnt[i].kpno;k++)
					{
						if(strcmp(token,tempchar[k])==0)
						{
							if(strstr(ala[i].name[k],"=")==NULL)
							{
								strcat(ch,ala[i].name[k]);
							}
							else
							{
								if(strcmp(ala[i].value[k],"")!=0)
								{
									strcat(ch,ala[i].value[k]);
								}
								else
								{
									for(l=0;l<mnt[i].kpno;l++)
									{
										if(strcmp(ptab[i].pname[k],kptab[i].kpname[l])==0)
											break;
									}
									strcat(ch,kptab[i].value[l]);
								}
							}
							strcat(ch," ");
							mdt_flag=1;
							break;
						}
					}
					if(mdt_flag==0)
					{
						strcat(ch,token);
						strcat(ch," ");
					}
					token=strtok(NULL,delim);
				}
				strcat(ch,"\n");
				fputs(ch,fpw);
			}
		}
		else
		{
			fputs(s1,fpw);
		}
		fgets(s,MAX,fpr);
		strcpy(s1,s);
	}
}
int main(void)
{
	macro_pass1();
	macro_pass2();
	return 0;
}
