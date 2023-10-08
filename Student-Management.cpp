#include<stdio.h>
#include<string.h>
#define MAXLENGTH 50
struct Subject{
    float Math;
    float Physics;
    float Chemistry;
};
struct Information{
    char Name[MAXLENGTH];
    char ID[MAXLENGTH];
    float GPA;
    int Age;
};
struct Student{
    Subject Subjects;
    Information Information;
};
struct Classroom{
    Student Students[MAXLENGTH];
    int Numbers;
};
void RemoveEnter(char A[]){
    int Lenth = strlen(A);
    if(A[Lenth-1] == '\n'){
        A[Lenth-1] = '\0';
    }
}
void Makenulllist(Classroom *Class){
    Class->Numbers = 0;
}
int Emptylist(Classroom Class){
    return Class.Numbers==0;
}
int Fulllist(Classroom Class){
    return Class.Numbers==MAXLENGTH;
}
int Firstlist(Classroom Class){
    return 1;
}
int Lastlist(Classroom Class){
    return Class.Numbers+1;
}
int NextPosition(Classroom Class, int Position){
    return Position+1;
}
int Prev(Classroom Class, int Position){
    return Position-1;
}
Student Retrieve(Classroom Class, int Position){
    return Class.Students[Position-1];
}
float GPA(float T, float L, float H){
    return (T+L+H)/3;
}
int Exist(Classroom Class, char ID[]){
    Student Element;
    int i = Firstlist(Class);
    while(i!=Lastlist(Class)){
        Element = Retrieve(Class,i);
        if(strcmp(ID,Element.Information.ID)==0){
            return 1;
        }
        i = NextPosition(Class,i);
    }
    return 0;
}
Student Addstudent(Classroom Class){
    Student Element;
    printf("Nhập vào tên sinh viên:\n");
    fgets(Element.Information.Name,MAXLENGTH,stdin);
    RemoveEnter(Element.Information.Name);
    ID:
    printf("Nhập vào id sinh viên:\n");
    fgets(Element.Information.ID,MAXLENGTH,stdin);
    RemoveEnter(Element.Information.ID);
    if(Exist(Class,Element.Information.ID)){
        printf("Đã tồn tại ID này!!!.\n");
        goto ID;
    }
    Age:
    printf("Nhập vào tuổi sinh viên:\n");
    scanf("%d",&Element.Information.Age);
    if(Element.Information.Age<1){
        printf("Tuổi không hợp lệ!!!.\n");
        goto Age;
    }
    Math:
    printf("Nhập vào điểm toán:\n");
    scanf("%f",&Element.Subjects.Math);
    if(Element.Subjects.Math<0||Element.Subjects.Math>10){
        printf("Điểm không hợp lệ!!!.\n");
        goto Math;
    }
    Physics:
    printf("Nhập vào điểm lý:\n");
    scanf("%f",&Element.Subjects.Physics);
    if(Element.Subjects.Physics<0||Element.Subjects.Physics>10){
        printf("Điểm không hợp lệ!!!.\n");
        goto Physics;
    }
    Chemistry:
    printf("Nhập vào điểm hóa:\n");
    scanf("%f",&Element.Subjects.Chemistry);
    if(Element.Subjects.Chemistry<0||Element.Subjects.Chemistry>10){
        printf("Điểm không hợp lệ!!!.\n");
        goto Chemistry;
    }
    float T = Element.Subjects.Math;
    float L = Element.Subjects.Physics;
    float H = Element.Subjects.Chemistry;
    Element.Information.GPA = GPA(T,L,H);
    return Element;
}
void Insert(Classroom *Class, int Position, Student Element){
    if(Fulllist(*Class)){
        printf("Lớp đã đầy sỉ số!!!\n");
    }else if(Position<Firstlist(*Class)||Position>Lastlist(*Class)){
        printf("Chỗ ngồi không hợp!!!\n");
    }else{
        for(int P = Class->Numbers;P>=Position;P--){
            Class->Students[P] = Class->Students[P-1];
        }
        Class->Numbers++;
        Class->Students[Position-1] = Element;
    }
}
void Delete(Classroom *Class, int Position){
    if(Emptylist(*Class)){
        printf("Còn ai trong lớp đâu mà xóa.\n");
    }else if(Position<Firstlist(*Class)||Position>Lastlist(*Class)-1){
        printf("Vị trí xóa không tồn tại.\n");
    }else{
        for(int P = Position;P<Lastlist(*Class)-1;P++){
            Class->Students[P-1] = Class->Students[P];
        }
        Class->Numbers--;
    }
}
void Readlist(Classroom *Class){
    Makenulllist(Class);
    Student Element;
    printf("Nhập vào số lượng sinh viên.\n");
    int Numbers;
    scanf("%d",&Numbers);
    for(int i=0;i<Numbers;i++){
        printf("\n");
        getchar();
        Element = Addstudent(*Class);
        Insert(Class,Lastlist(*Class),Element);
    }
}
void Printelement(Classroom Class, int Position){
    Student Element = Retrieve(Class,Position);
    printf("Thông tin sinh viên thứ %d\n",Position);
    printf("    - Họ và tên: %s\n",Element.Information.Name);
    printf("    - Mã số sinh viên: %s\n",Element.Information.ID);
    printf("    - Tuổi: %d\n",Element.Information.Age);
    printf("    - Điểm số các môn học:\n");
    printf("        + Toán: %.2f\n",Element.Subjects.Math);
    printf("        + Lý: %.2f\n",Element.Subjects.Physics);
    printf("        + Hóa: %.2f\n",Element.Subjects.Chemistry);
    printf("        + Điểm trung bình: %.2f\n\n",Element.Information.GPA);
}
void Printlist(Classroom Class){
    int Position = Firstlist(Class);
    while(Position!=Lastlist(Class)){
        Printelement(Class,Position);
        Position = NextPosition(Class,Position);
    }
    printf("\n");
}
void Swap(Student *A, Student *B){
    Student Temp = *A;
    *A = *B;
    *B = Temp;
}
void Dergee(Classroom *Class){
    int i = Firstlist(*Class);
    while(i!=Lastlist(*Class)-1){
        Student *EF = &Class->Students[i-1];
        int j = NextPosition(*Class,i);
        while(j!=Lastlist(*Class)){
            Student *EN = &Class->Students[j-1];
            if((*EF).Information.GPA<(*EN).Information.GPA){
                Swap(EF,EN);
            }
            j = NextPosition(*Class,j);
        }
        i = NextPosition(*Class,i);
    }
}
void Findstudent(Classroom Class){
    getchar();
    printf("Nhập vào mã số sinh viên cần tìm.\n");
    char ID[MAXLENGTH];
    fgets(ID,MAXLENGTH,stdin);
    RemoveEnter(ID);
    Student Element;
    int i = Firstlist(Class);
    while(i!=Lastlist(Class)){
        Element = Retrieve(Class,i);
        if(strcmp(ID,Element.Information.ID)==0){
            Printelement(Class,i);
            return;
        }
        i = NextPosition(Class,i);
    }
    printf("Không tìm thấy sinh viên có mã số %s",ID);
}
void Level(Classroom Class){
    Classroom Nhom[4];
    for(int i=0;i<4;i++){
        Makenulllist(&Nhom[i]);
    }
    Student Element;
    float Diem;
    int i = Firstlist(Class);
    while(i!=Lastlist(Class)){
        Element = Retrieve(Class,i);
        Diem = Element.Information.GPA;
        if(Diem>=9){
            Insert(&Nhom[0],Lastlist(Nhom[0]),Element);
        }else if(Diem>=7&&Diem<9){
            Insert(&Nhom[1],Lastlist(Nhom[1]),Element);
        }else if(Diem>=5&&Diem<7){
            Insert(&Nhom[2],Lastlist(Nhom[2]),Element);
        }else{
            Insert(&Nhom[3],Lastlist(Nhom[3]),Element);
        }
        i = NextPosition(Class,i);
    }
    for(int i=0;i<4;i++){
        printf("Danh sách sinh viên loại %d.\n",i+1);
        Printlist(Nhom[i]);
    }
}
void Change(Classroom *Class){
    printf("Bạn muốn thêm hay xóa sinh viên.\n");
    Return:
    printf("Nhập (1) nếu thêm, (2) nếu xóa và (-1) để thoát.\n");
    int Select;
    scanf("%d",&Select);
    if(Select==1){
        getchar();
        Student Element = Addstudent(*Class);
        printf("Nhập vào vị trí cần chèn vào.\n");
        int Position;
        scanf("%d",&Position);
        Insert(Class,Position,Element);
    }else if(Select==2){
        printf("Nhập mã số sinh viên cần xóa.\n");
        char ID[MAXLENGTH];
        getchar();
        fgets(ID,MAXLENGTH,stdin);
        RemoveEnter(ID);
        int i = Firstlist(*Class);
        while(i!=Lastlist(*Class)){
            if(strcmp(ID,Retrieve(*Class,i).Information.ID)==0){
                Delete(Class,i);
                return;
            }
            i = NextPosition(*Class,i);
        }
        printf("Không tìm thấy sinh viên cần xóa.\n");
    }else if(Select==-1){
        printf("Đã hủy thao tác này.\n");
    }else{
        printf("Bạn nhập sai thao tác, mời nhập lại.\n");
        goto Return;
    }
}
int main(int argc, char const *argv[]){
    Classroom Class;
    Root:
    int Select;
    printf("DANH SÁCH QUẢN LÝ SINH VIÊN LỚP HỌC.\n");
    printf("1 - Nhập vào danh sách sinh viên.\n");
    printf("2 - Xuất danh sách sinh viên.\n");
    printf("3 - Sắp xếp danh sách sinh viên theo thứ tự.\n");
    printf("4 - Tìm kiếm sinh viên bằng mã số sinh viên.\n");
    printf("5 - Phân loại sinh viên theo học lực.\n");
    printf("6 - Chỉnh sửa danh sách sinh viên(thêm hoặc xóa).\n");
    printf("0 - Nhập 0 để thoát.\n");
    printf("Nhập vào thao tác của bạn.\n");
    scanf("%d",&Select);
    switch(Select){
        case 1:
            Readlist(&Class);
            break;
        case 2:
            Printlist(Class);
            break;
        case 3:
            Dergee(&Class);
            Printlist(Class);
            break;
        case 4:
            Findstudent(Class);
            break;
        case 5:
            Level(Class);
            break;
        case 6:
            Change(&Class);
            break;
        case 0:
            printf("Thoát chương trình.\n");
            break;
        default:
            printf("Không có thao tác này.\n");
    }
    printf("\n");
    if(Select!=0) goto Root;
    return 0;
}