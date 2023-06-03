#include "stdio.h"

typedef struct user_data_stc* user_data;
typedef struct user_stc* user;

struct user_data_stc 
{
	char* name;
	unsigned long phone;
};

struct user_stc
{
	user_data usr_data;
	user prev;
	user next;
};

static user head, rear;
static unsigned int user_count = 0;
static user arr[10][10][10] = { 0 };

user find_user(unsigned int place)
{
	user iter = arr[place / 1000][(place % 1000) / 100][(place % 100) / 10];
	for (int i = 0; i < place % 10; i++)
	{
		iter = iter->next;
	}
	return iter;
}

unsigned int find_place(user usr)
{
	unsigned long usr_phone = usr->usr_data->phone;
	unsigned int iter_count = user_count / 20;
	unsigned int diff_count = iter_count;
	user iter;
	int result = 0;
	while (result == 0)
	{
		iter = find_user(iter_count);
		diff_count /= 2;
		if (usr_phone >= iter->usr_data->phone)
		{
			if (diff_count == 0)
			{
				result = 1;
			}
			iter_count -= diff_count;
		}
		else
		{
			iter_count += diff_count;
		}
	}
	iter_count *= 10;
	while (iter->usr_data->phone < usr_phone && iter->next != NULL)
	{
		iter = iter->next;
		iter_count += 1;
	}
	if (iter->next != NULL)
	{
		iter = iter->prev;
		iter_count -= 1;
	}
	return iter_count;
}

void update_arr(unsigned int place)
{
	unsigned int p_1000 = place / 1000;
	unsigned int p_100 = (place%1000) / 100;
	unsigned int p_10 = (place%100) / 10;
	unsigned int u_1000 = user_count / 1000;
	unsigned int u_100 = (user_count % 1000) / 100;
	unsigned int u_10 = (user_count % 100) / 10;
	for (unsigned int i = p_1000; i <= u_1000; i++)
	{
		for (unsigned int j = p_100; j <= u_100; j++)
		{
			for (unsigned int k = p_10; k <= u_10; k++)
			{
				if (i + j + k != 0)
				{
					arr[i][j][k] = arr[i][j][k]->prev;
				}
			}
			p_10 = 0;
		}
		p_100 = 0;
	}
	if (user_count % 10 == 0)
	{
		if (u_10 < 9) {
			arr[u_1000][u_100][u_10 + 1] = rear;
		}
		else {
			if (u_100 < 9) {
				arr[u_1000][u_100+1][0] = rear;
			}
			else {
				if (u_1000 < 9) {
					arr[u_1000 + 1][0][0] = rear;
				}
				else {
					printf("Arr is full!!");
				}
			}
		}
	}
}

void add_user(char* name, unsigned long phone)
{
	struct user_data_stc usr_data_stc = {name, phone};
	struct user_stc usr_stc = { &usr_data_stc, NULL, NULL };
	unsigned int place = find_place(&usr_stc);
	user temp = find_user(place);
	
	usr_stc.prev = temp;
	usr_stc.next = temp->next;
	temp->next = &usr_stc;
	if (usr_stc.next != NULL) {
		usr_stc.next->prev = &usr_stc;
	}
	else {
		rear = &usr_stc;
	}
	user_count += 1;
	update_arr(place);
}

int main() 
{
	struct user_data_stc init_usr_data ={"aaaaaaaaa", 000000000};
	struct user_stc init_usr = {&init_usr_data, NULL, NULL};
	head = &init_usr;
	arr[0][0][0] = head;
	rear = head;

	add_user("Hakan", 13124324);
	add_user("Hakan", 23124324);
	add_user("Hakan", 33124324);
	add_user("Hakan", 43124324);
	add_user("Hakan", 53124324);
	add_user("Hakan", 43124324);
	add_user("Hakan", 23124324);
	return 0;
}