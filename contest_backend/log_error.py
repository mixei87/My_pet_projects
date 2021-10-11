import sys
import datetime

count_list, counter = 0, 0
date = []
flag_print = 0
lines = list(sys.stdin)
for line in lines:
    if count_list == 0:
        t, e = map(int, line.split())
        count_list += 1
    else:
        ptr = line.find(' ', 22)
        status = line[22:ptr]
        if status == 'ERROR':
            counter += 1
            if e == 1:
                print(line[1:20], end='')
                flag_print = 1
                break
            else:
                year = int(line[1:5])
                month = int(line[6:8])
                day = int(line[9:11])
                hour = int(line[12:14])
                minute = int(line[15:17])
                second = int(line[18:20])
                date_tmp = datetime.datetime(year, month, day, hour, minute, second)
                date.append(date_tmp)
            if counter != 1:
                t1 = int((date[len(date)-1] - date[0]).total_seconds())
                if t1 >= t:
                    for i in range(len(date)-1):
                        date.pop(0)
                    counter = 1
                elif counter == e:
                    print(line[1:20], end='')
                    flag_print = 1
                    break
if flag_print == 0:
    print('-1', end='')
