/*****************************************************************************
*  OpenST Basic tool library                                                 *
*  Copyright (C) 2020 Delta Delta37@qq.com			                         *
*                                                                            *
*  This file is part of OST.                                                 *
*                                                                            *
*  This program is free software; you can redistribute it and/or modify      *
*  it under the terms of the GNU General Public License version 3 as         *
*  published by the Free Software Foundation.                                *
*                                                                            *
*  You should have received a copy of the GNU General Public License         *
*  along with OST. If not, see <http://www.gnu.org/licenses/>.               *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*  @file     translator.h                                                    *
*  @brief    Turn the syntax-analysis-tree to pseudo-assembly language.      *
*  Details.  Consist of the translation of expression and statement, the	 *
*            result only contains basic operating and transfer statement.    *
*  @author   Delta                                                           *
*  @email    Delta37@qq.com													 *
*  @version  1.0.0.1														 *
*  @date     2020/06/15		                                                 *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2020/06/15 | 1.0.0.1   | Delta          | define the virtual address      *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#pragma once
#include<vector>
#include<string>
#include"lexicalAnalysis.h"
#include"syntaxAnalysis.h"

#define TEMPORARY "通用寄存器"

#define DECLARE_TYPE "声明类型"
#define DECLARE_NUMBER "声明数量"
#define END_OF_PROGRAM "程序结束"
#define UNCONDITIONAL "无条件转移"
#define RESULT "结果寄存器"
#define IS_TRUE "结果寄存器为真则转移至"
#define IS_FALSE "结果寄存器为假则转移至"
#define OUTPUT "输出"
#define JUMP_TO "跳转至地址"

class translator
{
public:
	translator();
	~translator();
	size_t to_number(std::string str);
	std::vector<std::vector<std::pair<size_t,std::string>>> getExpTuple(generalTreeNode* root);
	std::vector<std::vector<std::pair<size_t, std::string>>> getTuple(generalTreeNode* root);
	size_t count_instruction(generalTreeNode* root);
private:
	std::pair<size_t, std::string > result;
};

