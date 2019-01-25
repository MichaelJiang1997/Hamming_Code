/*
// Last-Modified:2019-1-25 11:07:21
// Copyright (C)2019 SENCOM <sencom1997@outlook.com>
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERChamTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "hamming.h"

const char *encode(const char *src_code)
{
	int src_len = strlen(src_code);
	int ham_len;
	int i,c,b,h;
	int n;									//通用计数器
	char *ham_code = (char *)malloc(sizeof(char)*MAX_HAM_CODE_LEN);
	const char *ps = src_code;
	
	for(i = 0; i < MAX_HAM_CHECK_LEN; i++)		
	{
		if(pow(2,i)-i >= src_len+1)
			break;
	}
	if(i == MAX_HAM_CHECK_LEN)
		return "OVERFLOW";
	ham_len = i + src_len;
	
	for(h = 0 ; h < ham_len ; h++)			  //将源码放到汉明码中正确的位置上
	{
		ham_code[h] = 'c';			  		  //此位置为校验位用 'c' 标记
		for(c = 0 ; c < i ; c++)
		{ 
			if(pow(2,c) == h+1)
				break;
		}
		if(c == i)
			ham_code[h] = *ps++;
	}
	
	int each_h;						
	for(c = 0; c < i; c++)						//将校验码放到汉明码中正确的位置上(使用配偶原则)
	{
		b = -1;									//初始化 b
		for(h = 0; h < ham_len; h++)
		{
			each_h = h+1;
			for(int k = 0; k < c; k++) each_h = each_h >> 1;
			if( each_h % 2 == 1 && ham_code[h] != 'c')
			{
				if(b == -1)						//b第一次赋ham_code[]值
					b = ham_code[h]-48;
				else
					b = b ^ (ham_code[h]-48);
			}
		}
		for(n = 0; n < ham_len; n++)			//将 ham_code[] 中 ‘c’ 替换成相应的校验码
		{
			if(ham_code[n] == 'c')
			{
				ham_code[n] = b+48;
				break;
			}
		}
	}
	ham_code[ham_len] = '\0';
	return ham_code;
}

int is_error(const char* ham_code)
{
	int ham_len = strlen(ham_code);
	int k,n,p,h,c;
	int error_code = 0;							//存放错误码(十进制)
	int pn[MAX_HAM_CHECK_LEN];					//存放错误码(二进制)
	
	for(k = 2; k < MAX_HAM_CHECK_LEN; k++)		//计算出校验位的个数 k
	{
		if(pow(2,k) >= ham_len + 1)
			break;
	}
	
	int each_h;						
	for(c = 0; c < k; c++)						//将校验码放到汉明码中正确的位置上(使用配偶原则)
	{
		p = -1;									//初始化 p
		for(h = 0; h < ham_len; h++)
		{
			each_h = h+1;
			for(int k = 0; k < c; k++) each_h = each_h >> 1;
			if( each_h % 2 == 1)
			{
				if(p == -1)						//p第一次赋 ham_code[] 值
					p = ham_code[h]-48;
				else
					p = p ^ (ham_code[h]-48);
			}
		}
		pn[c] = p;
	}
	c = 0;										//位移计数器初始化
	for(n = 0; n < k; n++)						//将 pn[] 中二进制错误码转十进制存入 error_code 中
		error_code += pn[n] << c++;
	return error_code;
}

const char* check_error(const char* ham_code)
{
	int error_index = 0;
	char *true_ham_code = (char *)malloc(sizeof(char)*MAX_HAM_CODE_LEN);
	strcpy(true_ham_code,ham_code);
	if( error_index = is_error(ham_code) ){
		true_ham_code[error_index-1] == '0' ? true_ham_code[error_index-1] = '1' : true_ham_code[error_index-1] = '0';
		return true_ham_code;
	}
	else
		return true_ham_code;
}

const char* decode(const char* ham_code)
{
	char *src_code = (char *)malloc(sizeof(char)*MAX_HAM_CODE_LEN);
	const char *true_ham_code;
	int ham_len = strlen(ham_code);
	int i=0,h,k,c;
	
	if(is_error(ham_code) )						//检查是否有错并纠正错误位
		true_ham_code = check_error(ham_code);
	else
		true_ham_code = ham_code;
	for(k = 2; k < MAX_HAM_CHECK_LEN; k++)		//计算出校验位的个数 k
	{
		if(pow(2,k) >= ham_len + 1)
			break;
	}
	
	for(h = 0 ; h < ham_len ; h++)			  //从正确的汉明码中分解出源码
	{
		for(c = 0 ; c < k ; c++)
		{ 
			if(pow(2,c) == h+1)
				break;
		}
		if(c == k)
			src_code[i++] = true_ham_code[h];
	}
	src_code[i] = '\0';
	return src_code;
}