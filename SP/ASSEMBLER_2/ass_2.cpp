/*
 * ass.cpp
 *
 *  Created on: 06-Jan-2016
 *      Author: aseem
 */
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<cstdlib>
class format
{	std::string mnemonic,ins_class;
	int code,no;
	friend class assembler;
};
class res
{
	int i,j;
	friend class assembler;
};
class lit
{
	std::string s;
	int add;
	friend class assembler;
};
class assembler
{	format table[26][5];
	lit littab[10];
	int pooltab[5],pb,pl;
	int bucket[26],s,l,l2;
	std::string pass1[30],pass2[30];
	public:
		assembler()
		{	s=l=l2=pb=0;
			pooltab[0]=0;
			pl=1;
			for(int i=0;i<26;i++)
				bucket[i]=0;
		}

		void populate()
		{	std::string line,token;
			int j,num;
			std::ifstream fp("optab_lit.txt");
			if(fp.is_open())
			{
				while(!fp.eof())
				{	std::getline(fp,line);
					j=(int)line[0]-97;
					if(j<0)
						break;
					std::istringstream iss(line);
					iss>>token;
					table[j][bucket[j]].mnemonic=token;
					iss>>token;
					table[j][bucket[j]].ins_class=token;
					iss>>num;
					table[j][bucket[j]].code=num;
					iss>>num;
					table[j][bucket[j]].no=num;
					bucket[j]++;
				}
			    fp.close();
			}
		}
		void print_table()
		{
			for(int i=0;i<26;i++)
			{
				for(int j=0;j<bucket[i];j++)
				{
					std::cout<<"\nValue at "<<i<<" "<<j<<":";
					std::cout<<table[i][j].code<<" "<<table[i][j].ins_class<<" "<<table[i][j].mnemonic;
				}
			}
		}
		res search_op(std::string s)
		{
			res r;
			r.i=s[0]-97;
			for(int i=0;i<bucket[r.i];i++)
				if(table[r.i][i].mnemonic.compare(s)==0)
				{	r.j=i;
					return r;
				}
			r.i=r.j=-1;
			return r;
		}
		int search_lit(std::string str,int b)
		{
			for(int i=b;i<s;i++)
				if(str.compare(littab[i].s)==0)
					return i;
			return -1;
		}
		void add_lit(std::string str,int add)
		{
			littab[s++].s=str;
			littab[s-1].add=add;
		}
		char isreg(std::string s)

		{
			if(s.compare("areg")==0)
				return '1';
			if(s.compare("breg")==0)
				return '2';
			if(s.compare("creg")==0)
				return '3';
			if(s.compare("dreg")==0)
				return '4';
			return '0';

		}
		void pass_I()
		{	int lc=0,itoken;
			res r;
			std::string line,token;
			std::ifstream fp("source_code_lit.txt");
			while(!fp.eof())
			{
				std::getline(fp,line,'\n');
				std::istringstream iss(line);
				iss>>token;
				if(token.compare("start")==0)
				{	iss>>itoken;
					lc=itoken;
					std::ostringstream op;
					op<<itoken;
					pass1[l++]=op.str()+" ad , 1 - c , "+op.str();
					continue;
				}
				r=search_op(token);
				if(r.i==-1)
				{
					std::cout<<"\nInvalid instruction at line "<<l+1;
					exit(0);
				}
				if(r.i!=-1)
				{
					format f=table[r.i][r.j];
					std::ostringstream o1,o2,o3;
					o1<<lc;
					if(f.ins_class.compare("is")==0)
						lc++;
					o2<<f.code;
					pass1[l]=o1.str()+" "+f.ins_class+" , "+o2.str()+" ";
					iss>>token;
					if(f.no==0)
					{
						l++;
						if(f.mnemonic.compare("ltorg")==0)
						{
							pb=s;
							pooltab[pl++]=s;
						}
						continue;
					}
					if(f.no==1)
					{

						if(isreg(token)!='0')
							pass1[l]+=isreg(token);
						else
						{
							int pos=search_lit(token,pb);
							if(pos==-1)
								add_lit(token,lc-1);
							o3<<search_lit(token,pb);
							pass1[l++]+="- l , "+o3.str();
						}

					}
					if(f.no==2)
					{

						if(isreg(token)!='0')
							pass1[l]+=isreg(token);
						else
						{
							std::cout<<"invalid register or format at line "<<l+1;
							exit(0);
						}
						iss>>token;
						iss>>token;
						int pos=search_lit(token,pb);
						if(pos==-1)
							add_lit(token,lc-1);
						o3<<search_lit(token,pb);
						pass1[l++]+=" l , "+o3.str();

					}

				}


			}
		}
		void op_pass1()
		{	std::ofstream file("pass1.txt");

			for(int i=0;i<l;i++)
			{	std::cout<<pass1[i]<<std::endl;
				file<<pass1[i]<<std::endl;
			}
			file.close();
		}
		void print_lit()
		{	std::cout<<"\nNo.\tLiteral\tAddress\n";
			for(int i=0;i<s;i++)
				std::cout<<i<<".\t"<<littab[i].s<<"\t"<<littab[i].add<<"\n";
		}
		void print_pool()
		{
			std::cout<<"\nNo.\tPool Start\n";
			for(int i=0;i<pl;i++)
				std::cout<<i<<".\t"<<pooltab[i]<<"\n";

		}
		void pass_II()
		{
			int c=00;
			std::string token;
			int no;
			for(int i=0;i<l;i++)
			{
				std::istringstream iss(pass1[i]);
				iss>>no;
				iss>>token;
				if(token.compare("is")!=0)
				{
					std::ostringstream o1;
					o1<<"+"<<no<<" ";
					pass2[l2++]=o1.str();
					if(pass1[i].find("ad , 3")!=std::string::npos)
					{
						for(int k=pooltab[c];k<pooltab[c+1];k++)
						{
							std::ostringstream o2;
							o2<<"+"<<no++<<" ";
							pass2[l2++]=o2.str();
						}
						c++;
					}
					continue;
				}
				else
				{
					std::ostringstream o1;
					o1<<"+"<<no<<" ";
					iss>>token;
					iss>>token;
					o1<<token<<" ";
					iss>>token;
					o1<<token<<" ";
					iss>>token;
					iss>>token;
					iss>>no;
					int d=littab[no].add;
					o1<<d;
					pass2[l2++]=o1.str();
				}
			}
			for(int k=pooltab[c];k<s;k++)
			{
				std::ostringstream o2;
				o2<<"+"<<++no<<" ";
				pass2[l2++]=o2.str();
			}
		}
		void  op_pass_II()
		{	std::ofstream file("pass2.txt");
			for(int i=0;i<l2-1;i++)
			{	std::cout<<pass2[i]<<std::endl;
				file<<pass2[i]<<std::endl;
			}
			file.close();
		}
};
int main(void)
{
	assembler op;
	op.populate();
	op.pass_I();
	std::cout<<"\nOutput PassI:\n";
	op.op_pass1();
	std::cout<<"\nLiteral Table:\n";
	op.print_lit();
	std::cout<<"\nPool Table:\n";
	op.print_pool();
	op.pass_II();
	std::cout<<"\nOutput PassII:\n";
	op.op_pass_II();
	return 0;
}


