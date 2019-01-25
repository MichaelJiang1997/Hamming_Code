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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef HAMMING_H
#define HAMMING_H

#include "string.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

#define TRUE      		  1
#define FALSE			  0
#define MAX_HAM_CHECK_LEN 32 					//最大校验位个数
#define MAX_HAM_CODE_LEN  256					//最大汉明码长度

/*
汉明码校验位个数(k)应满足：
2^k >= n+k+1
其中 n 为源码长度
*/

const char* encode(const char* src_code);		//编码, 返回汉明码
int is_error(const char* ham_code);				//判断是否有错,	若有错返回错误位置,若无错返回 0
const char* check_error(const char* ham_code);	//校验错误,返回正确的汉明码
const char* decode(const char* ham_code);		//解码(带校验)

#endif
