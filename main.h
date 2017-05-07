/*
 * Header
 *
 * Copyright (C) 2017 Group F Mail System Project
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define NAMELENGTH 30
#define MAILLENGTH 30
#define GROUPLENGTH 30
#define SEXLENGTH 30

// data structure, typedef as "data"
typedef struct data
{
	int id;
	char name[NAMELENGTH];
	char sex[SEXLENGTH];
	char mail[MAILLENGTH];
	char group[GROUPLENGTH];
	struct data *next;
} data;

// backup data structure, typedef as "backupdata"
typedef struct backupData
{
	int operationCode;// 1 - Deleted 2 - Edited 3 - Created
	int id;
	char name[NAMELENGTH];
	char sex[SEXLENGTH];
	char mail[MAILLENGTH];
	char group[GROUPLENGTH];
} backupdata;

// Zhou Fang
void FlushBuffer();
void StringInLine(char *string);
void GetString(char *string, int length);
void ClearScreen();
void ShowTitle();
void ShowMain(int changeCounter);
int  FreeData(data *startData, data *endData);


int  LoadData(char *filePath, data **startData, data **endData, int *dataNumber);
int  GetOperation();
int  MainOperation(int operateCode, int *changeCounter, data *startData, data *endData, int *dataNumber,
                  backupdata *backup, char *filePath);
int  FindID(data *startData, data *endData, int dataNumber, char *subTitle);

void DataCreateUI(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter);
void DataReadUI(data *startData, data *endData, int dataNumber);
void DataUpdateUI(data *startData, data *endData, int dataNumber, backupdata *backupData, int *changeCounter);
void DataDeleteUI(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter);

int  DataRead(data *startData, data *endData, int dataID);
int  DataReadEdited(data *startData, data *endData, data *editedData, int dataID);
int  DataReadAll(data *startData, data *endData);

// Tatsuya Kawamura
int DataCreate(data **startData, data **endData, data *newData, int *dataNumber, backupdata *backupData, int mode);

// Atsushi Hasegawa
int  DataUpdate(data *startData, data *endData, data *editedData, int dataID, backupdata *backupData);

// Yuto Takebayashi
int  DataDelete(data *startData, data *endData, int dataID, int *dataNumber, backupdata *backupData);

// Masuda Tatsuki
int  DataRedo(data *startData, data *endData, int *dataNumber, backupdata *backupData, int *changeCounter);

// Ryosuke Ukita
int SaveData(char *filePath,data *startData, data *endData);