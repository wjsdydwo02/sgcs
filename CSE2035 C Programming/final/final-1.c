#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ROOM_ {
	int number;
	char name[21];
} room;

typedef struct _BUILDING_ {
	char name[3];
	int number_of_rooms;
	struct _ROOM_* rooms;
} building;

void readBuildingInfo(char* filename, building** data, int* number_of_buildings);

char* searchBuildingInfo(building* data, int number_of_buildings, char* room_number);

int roomcmp(building b, room r, char* query);

void freeBuildingInfo(building* data);

int main() {
	char filename[21], query[7];
	scanf("%s", filename);
	scanf("%s", query);

	building* data;
	int number_of_buildings;

	readBuildingInfo(filename, &data, &number_of_buildings);

	printf("%s\n", searchBuildingInfo(data, number_of_buildings, query));
	
	freeBuildingInfo(data);

	return 0;
}

char* searchBuildingInfo(building* data, int number_of_buildings, char* room_number) {
	for (int i = 0; i < number_of_buildings; i++) {
		for (int j = 0; j < data[i].number_of_rooms; j++) {
			room r = data[i].rooms[j];

			if (roomcmp(data[i], r, room_number)) {
				return data[i].rooms[j].name;
			}
		}
	}

	return "Not found";
}

int roomcmp(building b, room r, char* query) {
	for (int i = 0; i < 2; i++) {
		if (b.name[i] != query[i]) return 0;
	}
	
	if (r.number / 1000 != query[2] - '0') return 0;
	if ((r.number / 100) % 10 != query[3] - '0') return 0;
	if ((r.number / 10) % 10 != query[4] - '0') return 0;
	if (r.number % 10 != query[5] - '0') return 0;

	return 1;
}

void readBuildingInfo(char* filename, building** data, int* number_of_buildings) {
	int n;

	FILE* file = fopen(filename, "r");
	
	fscanf(file, "%d", number_of_buildings);
	*data = (building*)malloc(sizeof(building) * (*number_of_buildings));

	for (int i = 0; i < *number_of_buildings; i++) {
		fscanf(file, "%s", (*data)[i].name);
		fscanf(file, "%d", &((*data)[i].number_of_rooms));

		(*data)[i].rooms = (room*)malloc(sizeof(room) * (*data)[i].number_of_rooms);

		for (int j = 0; j < (*data)[i].number_of_rooms; j++) {
			fscanf(file, "%d", &((*data)[i].rooms[j].number));
			fscanf(file, "%s", (*data)[i].rooms[j].name);
		}
	}

	fclose(file);
}

void freeBuildingInfo(building* data) {
	for (int i = 0; i < data->number_of_rooms; i++) {
		free(data->rooms);
	}
	free(data);
}