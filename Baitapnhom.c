#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char id[16];
    char name[50];
    char birthday[16];
    char sex[8];
    char phone[20];
};

void trim_newline(char s[]) {
    int len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

void print(struct Student students[], int n) {
    int i;
    if (n == 0) {
        printf("Danh sach sinh vien rong!!\n");
        return;
    }

    printf("\n%-10s | %-25s | %-10s | %-6s | %-12s\n",
           "ID", "NAME", "BIRTHDAY", "SEX", "PHONE");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10s | %-25s | %-10s | %-6s | %-12s\n",
               students[i].id, students[i].name, students[i].birthday,
               students[i].sex, students[i].phone);
    }
}

int addStudent(struct Student ds[], int n) {
    struct Student sv;
    int i;

    if (n >= MAX_STUDENTS) {
        printf("Danh sach da day, khong the them!\n");
        return n;
    }

    printf("Ma SV: ");
    fgets(sv.id, sizeof(sv.id), stdin);
    trim_newline(sv.id);

    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].id, sv.id) == 0) {
            printf("Ma sinh vien da ton tai!\n");
            return n;
        }
    }

    printf("Ho ten: ");
    fgets(sv.name, sizeof(sv.name), stdin);
    trim_newline(sv.name);

    printf("Ngay sinh: ");
    fgets(sv.birthday, sizeof(sv.birthday), stdin);
    trim_newline(sv.birthday);

    printf("Gioi tinh: ");
    fgets(sv.sex, sizeof(sv.sex), stdin);
    trim_newline(sv.sex);

    printf("So dien thoai: ");
    fgets(sv.phone, sizeof(sv.phone), stdin);
    trim_newline(sv.phone);

    ds[n] = sv;
    printf("Them thanh cong!\n");
    return n + 1;
}

void editStudent(struct Student ds[], int n) {
    char id[16];
    int i, found = 0;

    printf("Nhap ma SV can sua: ");
    fgets(id, sizeof(id), stdin);
    trim_newline(id);

    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].id, id) == 0) {
            found = 1;
            printf("Ho ten moi: ");
            fgets(ds[i].name, sizeof(ds[i].name), stdin);
            trim_newline(ds[i].name);

            printf("Ngay sinh moi: ");
            fgets(ds[i].birthday, sizeof(ds[i].birthday), stdin);
            trim_newline(ds[i].birthday);

            printf("Gioi tinh moi: ");
            fgets(ds[i].sex, sizeof(ds[i].sex), stdin);
            trim_newline(ds[i].sex);

            printf("SDT moi: ");
            fgets(ds[i].phone, sizeof(ds[i].phone), stdin);
            trim_newline(ds[i].phone);

            printf("Sua thanh cong!\n");
            break;
        }
    }

    if (!found)
        printf("Khong tim thay ma SV!\n");
}

int deleteStudent(struct Student ds[], int n) {
    char id[16];
    int i, j, found = 0;

    printf("Nhap ma SV can xoa: ");
    fgets(id, sizeof(id), stdin);
    trim_newline(id);

    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].id, id) == 0) {
            for (j = i; j < n - 1; j++) {
                ds[j] = ds[j + 1];
            }
            printf("Xoa thanh cong!\n");
            found = 1;
            n--;
            break;
        }
    }

    if (!found)
        printf("Khong tim thay ma SV!\n");

    return n;
}

void searchStudent(struct Student ds[], int n) {
    char key[64];
    int i, found = 0;

    printf("Nhap ten hoac ma can tim: ");
    fgets(key, sizeof(key), stdin);
    trim_newline(key);

    for (i = 0; i < n; i++) {
        if (strstr(ds[i].name, key) != NULL || strcmp(ds[i].id, key) == 0) {
            printf("Tim thay: %s - %s - %s - %s - %s\n",
                   ds[i].id, ds[i].name, ds[i].birthday,
                   ds[i].sex, ds[i].phone);
            found = 1;
        }
    }

    if (!found)
        printf("Khong tim thay sinh vien!\n");
}

int main() {
    struct Student arrStudents[MAX_STUDENTS];
    int n = 0;
    int choice;
    char buf[32];

    do {
        printf("\n--- MENU ---\n");
        printf("1. Them sinh vien\n");
        printf("2. Sua sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Tim kiem sinh vien\n");
        printf("5. In danh sach\n");
        printf("6. Thoat\n");
        printf("Lua chon cua ban: ");

        if (!fgets(buf, sizeof(buf), stdin))
            continue;

        trim_newline(buf);
        sscanf(buf, "%d", &choice);

        if (choice == 1)
            n = addStudent(arrStudents, n);
        else if (choice == 2)
            editStudent(arrStudents, n);
        else if (choice == 3)
            n = deleteStudent(arrStudents, n);
        else if (choice == 4)
            searchStudent(arrStudents, n);
        else if (choice == 5)
            print(arrStudents, n);
        else if (choice == 6)
            printf("Thoat chuong trinh.\n");
        else
            printf("Lua chon khong hop le!\n");

    } while (choice != 6);

    return 0;
}

