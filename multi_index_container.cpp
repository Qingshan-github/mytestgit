#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>
using namespace std;
using namespace boost::multi_index;
using boost::multi_index_container;
struct Students;
struct WeekCourseList;
struct StuClass;
struct WeekCourseList{
public:
	WeekCourseList(){};
	unsigned int Date;
	enum EnumCourseList{
		YuWen = 0,
		ShuXue,
		YingYu,
		HuaXue,
		JiSuanJi,
		YingYue,
		TiYu,
		WuLi,
		MeiShu
	};
	enum EnumWeekList{
		Sunday = 0,
		Monday,
		Tuesday,
		Wednesday,
		Thursday,
		Friday,
		Saturday
	};
	
	void setEnumCourse(const EnumCourseList & index) ;
private:

	vector<EnumCourseList> my_courseList;
};
void WeekCourseList::setEnumCourse(const EnumCourseList &index) {
	this->my_courseList.push_back(index);
}

struct StuClass : public WeekCourseList{
		
public :
		

		StuClass(){_Grade="",_SecondClass="";};

		StuClass(std::string grade,std::string second ):_Grade(grade),_SecondClass(second){};

		void setClassGrade(std::string grade,std::string second ){
			_Grade = grade
			,_SecondClass = second;
		};
		
		void setGrade(std::string grade){
			_Grade = grade;
		}
		void setClass(std::string Class){
			_SecondClass = Class ;
		}
		std::string getGrade(){
			return _Grade ;
		}
		std::string getClass(){
			return _SecondClass  ;
		}
		
		friend std::ostream &operator << (ostream &os,const StuClass&p);

private:
		std::string _Grade;
		std::string _SecondClass;
};
std::ostream &operator << (ostream &os,const StuClass&p)
{
		os<<"Grade: "<<p._Grade <<"    class: "<<p._SecondClass<<"\n";
		return os;
}


struct Students
{
public:
	Students(){};
	Students(int id ,unsigned int age,unsigned int height,std::string name)
	:id_card(id),my_age(age),my_height(height),my_name(name)
	{};
	int id_card;
	unsigned int my_age;
	std::string my_name;
	unsigned int my_height;
	std::set<StuClass> my_class;
	friend std::ostream &operator << (ostream &os, Students &p)
	{	
		os<<"ID: "<<p.id_card <<"    Age: "<<p.my_age<<"    Name: "<<p.my_name<<"    Height: "<<p.my_height<<"\n";
		
		return os;
	}
	
};
#if 0
std::ostream &operator << (ostream &os, Students (&p) [10])
{	
		for(unsigned int i = 0; i < 10; i++)
			os<<"ID: "<<p[i].id_card <<"    Age: "<<p[i].my_age<<"    Name: "<<p[i].my_name<<"    Height: "<<p[i].my_height<<"\n";
		
		return os;
}
#endif
struct by_name{};
struct by_age{};
struct by_id{};
struct by_height{};

 typedef boost::multi_index_container<Students,
 		indexed_by< ordered_unique<	tag<by_id>,member<Students,int,&Students::id_card	>>,
		 ordered_non_unique<tag<by_name>,member<Students,std::string,&Students::my_name>>
		> > Students_Index;
template<typename T ,int N>
void create_random_(T (& st)[N]){
	for(unsigned int i = 0; i < N; i++){
			st[i] = T(i+1*2,i+10*i,i+160,(string("qingshan")+std::to_string(i)));
	}
}



int main(int argc ,char ** argv){
	 Students g_Students[10];
	//StuClass stu("1","2");
	create_random_ <Students,10>( g_Students);
	//std::cout<<g_Students ;
	std::cout<<"------------------------\n";
	

 	Students_Index Studentssets;
	 Studentssets.insert(g_Students[0]);
 	 Studentssets.insert(g_Students[1]);
 	 Studentssets.insert(g_Students[2]);
 	 Studentssets.insert(g_Students[3]);
 	 Studentssets.insert(g_Students[4]);
	
	std::cout<<g_Students[0];
	Students_Index::index<by_name>::type& indexOfName = Studentssets.get<by_name>();  
	if (indexOfName.find("qingshan1") != indexOfName.end()){

		std::cout<<"find\n";
	}
	typedef Students_Index::nth_index<0>::type IDIndex;
	IDIndex &IdIndex = Studentssets.get<0>();
	//copy(IdIndex.begin(),IdIndex.end(),ostream_iterator<Students>(cout));
	return 0;
}
