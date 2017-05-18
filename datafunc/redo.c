/*
 * Data Function - Redo
 * 
 * Author: Masuda Tatsuki
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
 * ╦═╗╔═╗╔╦╗╔═╗
 * ╠╦╝║╣  ║║║ ║
 * ╩╚═╚═╝═╩╝╚═╝
 * Author: Masuda Tatsuki
 * Last Update: Zhou Fang @ 5/18/2017
 * Redo function.
 * @param {data**} startData where the data start.
 * @param {data**} endData where the data end.
 * @param {int*} dataNumber to display the number of data.]
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataRedo(data **startData, data **endData, int *dataNumber, backupdata *backupData, int *changeCounter)
{
    int resultCode = 0;
    data *tempData;

    (*changeCounter)--;

    tempData = (data *)calloc(1, sizeof(data));
    tempData->id = backupData->id;
    strcpy(tempData->name, backupData->name);
    strcpy(tempData->mail, backupData->mail);
    strcpy(tempData->sex, backupData->sex);
    strcpy(tempData->group, backupData->group);

    switch(backupData->operationCode)
    {

        case 1: // Deleted
            DataCreate(startData, endData, tempData, dataNumber, backupData, 2);
            break;
        case 2: // Edited
            DataUpdate(*startData, *endData, tempData, backupData->id, backupData);
            free(tempData);
            break;
        case 3: // Created
            DataDelete(startData, endData, backupData->id, dataNumber, backupData);
            free(tempData);
            break;
        default:
            free(tempData);
            break;
    }

    return resultCode;
}