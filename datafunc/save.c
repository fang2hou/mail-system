/*
 * Data Function - Save
 * 
 * Author: Ryosuke Ukita
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

/**
 * Author: Ryosuke Ukita
 * Last Update: Zhou Fang @ 5/7/2017
 * Save data to file.
 * @param {char*} filePath The path of data file.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 */
int SaveData(char *filePath,data *startData, data *endData)
{
    FILE *CSVFile;
    data *data;
    data = startData;

    CSVFile = fopen(filePath,"w");

    fprintf(CSVFile,"#Id,Name,Sex,Mail address,Group");

    while (data != NULL)
    {
        fprintf(CSVFile,"\n%d,%s,%s,%s,%s", data -> id, data -> name, data -> sex, data -> mail, data -> group);
        data = data -> next;
    }

    fclose(CSVFile);

    return 1;
}