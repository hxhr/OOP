/* 2250748 �����q �Ű� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* �˴�������ӱ���Ķ����������������ȫ�ֱ����� */
//ѧ���ˡ�������
class Teacher;  // ǰ������
/* Student ��Ķ��壨��Ա��������������ʵ�֣� */
class Student {
private:
	int num;	//ѧ��
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Student();
	Student(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Student &stu);
	//���в���������ӳ�Ա����������ʵ�֣���������������ݳ�Ա����Ԫ����
	// ��ֵ�������������
	Student& operator=(const Teacher& teacher);

	// ת������������
	operator Teacher() const;
};

/* ----����Student���Ա��������Ԫ����������ʵ�֣������޷��ڴ˴�ʵ�ֵĺ�������������ţ�---- */
Student::Student() : num(2150000), sex('M')
{
	strcpy(name, "<ѧ��S>");
	strcpy(addr, "��ƽ·1239��");
}

Student::Student(const int num1, const char* name1, const char sex1, const char* addr1) : num(num1), sex(sex1)
{
	strncpy(name, name1, 15);
	name[15] = '\0';
	strncpy(addr, addr1, 63);
	addr[63] = '\0';
}
ostream& operator<<(ostream& out, const Student& stu)
{
	out << stu.num << " " << stu.name << " " << stu.sex << " " << stu.addr;
	return out;
}




/* Teacher ��Ķ���(Teacher���в�����������κ����ݳ�Ա����Ա��������Ԫ����Ա��������������ʵ��) */
class Teacher {
private:
	int num;	//����
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Teacher();
	Teacher(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Teacher &te);
	friend class Student;
	//���в��ֲ���������κ�����
};


/* ----����Teacher���Ա��������Ԫ����������ʵ��---- */
Teacher::Teacher() : num(21000), sex('M')
{
	strcpy(name, "<��ʦT>");
	strcpy(addr, "��ƽ·1239���Ժ�¥");
}
Teacher::Teacher(const int num1, const char* name1, const char sex1, const char* addr1) : num(num1), sex(sex1)
{
	strncpy(name, name1, 15);
	name[15] = '\0';
	strncpy(addr, addr1, 63);
	addr[63] = '\0';
}
ostream& operator<<(ostream& out, const Teacher& te)
{
	out << te.num << " " << te.name << " " << te.sex << " " << te.addr;
	return out;
}

/* ----����Studentr���б�����Teacher��ʵ�ֵĳ�Ա����������ʵ��---- */

Student& Student::operator=(const Teacher& teacher)
{
	num = 2150000 + teacher.num % 1000;  // ����תѧ�Ź���
	strcpy(name, "ѧ��");
	strncat(name, teacher.name + 4, 10);  // ����ת������
	sex = teacher.sex;  // �Ա�ת������
	strcpy(addr, teacher.addr);  // ��ַת������
	strcat(addr, "101��");

	return *this;
}

Student::operator Teacher() const 
{
	Teacher teacher;
	teacher.num = 21000 + num % 1000;  // ѧ��ת���Ź���
	strcpy(teacher.name, "��ʦ");
	strncat(teacher.name, name + 4, 10);  // ����ת������
	teacher.sex = sex;  // �Ա�ת������
	strcpy(teacher.addr, addr);  // ��ַת������
	strcat(teacher.addr, "����ѧԺ");

	return teacher;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	Student s1;	//ȱʡֵ - ѧ�ţ�2150000 ������<ѧ��S> �Ա�M ��ַ����ƽ·1239��
	Student s2 = Student(2151234, "ѧ����", 'M', "�ܰ���·4800��");
	Teacher t1;	//ȱʡֵ - ���ţ�21000 ������<��ʦT> �Ա�M ��ַ����ƽ·1239���Ժ�¥
	Teacher t2 = Teacher(21123, "��ʦA", 'F', "�ܰ���·4800�����Ź�");

	/* ��ӡԭʼѧ����Ϣ */
	cout << "ѧ����Ϣ��" << s1 << endl;				//���������"ѧ����Ϣ��2150000 <ѧ��S> M ��ƽ·1239��"
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��2151234 ѧ���� M �ܰ���·4800��"
	cout << endl;

	/* ��ӡԭʼ��ʦ��Ϣ */
	cout << "��ʦ��Ϣ��" << t1 << endl;				//���������"��ʦ��Ϣ��21000 <��ʦT> M ��ƽ·1239���Ժ�¥"
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��21123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << endl;

	/* ѧ��ת��ʦ���ԣ�
		ѧ��ת���Ź��򣺹��� = 21 + ѧ�ź���λ
		����ת������ǰ��������ת��Ϊ"��ʦ"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"����ѧԺ"(�������ַ���Խ��)    */
	t1 = s2;
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��2151234 ѧ���� M �ܰ���·4800��"
	cout << "ת��Ϊ��ʦ����Ϣ��" << t1 << endl;		//���������"ת��Ϊ��ʦ����Ϣ��21234 ��ʦ�� M �ܰ���·4800�ŵ���ѧԺ"
	cout << endl;

	/* ��ʦתѧ�����ԣ�
		����תѧ�Ź���ѧ�� = 2150 + ���ź���λ
		����ת������ǰ��������ת��Ϊ"ѧ��"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"101��"(�������ַ���Խ��)    */
	s1 = t2;
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��21123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << "ת��Ϊѧ������Ϣ��" << s1 << endl;		//���������"ת��Ϊѧ������Ϣ��2150123 ѧ��A F �ܰ���·4800�����Ź�101��"
	cout << endl;

	return 0;
}
