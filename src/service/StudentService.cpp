#include "StudentService.hpp"

#include <iostream>

StudentService::StudentService(
    Database &db,
    StudentRepository &studentRepo,
    PersonRepository &personRepo,
    ClassRepository &classRepo,
    MajorRepository &majorRepo,
    CollegeRepository &collegeRepo)
    : db(db),
      studentRepo(studentRepo),
      personRepo(personRepo),
      classRepo(classRepo),
      majorRepo(majorRepo),
      collegeRepo(collegeRepo)
{
}

void StudentService::showStudentDetail(
    int studentId)
{
    auto student =
        studentRepo.findByPersonId(
            studentId);

    if (!student)
    {
        std::cout
            << "Student not found\n";

        return;
    }

    auto person =
        personRepo.findById(
            student->getPersonId());

    auto Class =
        classRepo.findById(
            student->getClassId());

    auto major =
        majorRepo.findById(
            Class->getMajorId());

    auto college =
        collegeRepo.findById(
            major->getCollegeId());

    std::cout
        << "姓名: "
        << person->getName()
        << '\n';

    std::cout
        << "班级: "
        << Class->getClassNumber()
        << '\n';

    std::cout
        << "专业: "
        << major->getName()
        << '\n';

    std::cout
        << "学院: "
        << college->getName()
        << '\n';
}

std::vector<StudentSummary> StudentService::listAllStudents()
{

    /*
    StudentSummary
    {
        int personId = 0;
        std::string name;
        std::string gender;
        std::string className;
        std::string majorName;
        std::string collegeName;
        std::string residence;
    }
    */

    std::vector<StudentSummary> result;

    auto students = studentRepo.findAll();

    for (const auto &s : students)
    {

        auto person = personRepo.findById(s.getPersonId());

        auto classInfo = classRepo.findById(s.getClassId());

        auto major = majorRepo.findById(classInfo->getMajorId());

        auto college = collegeRepo.findById(major->getCollegeId());

        result.push_back({person->getId(),
                          person->getName(),
                          person->getNameType(),
                          person->getGender(),
                          person->getGenderConfidence(),
                          classInfo->getClassNumber(),
                          major->getName(),
                          college->getName(),
                          person->getResidence(),
                          person->getResidenceConfidence()});
    }

    return result;
}

std::vector<College> StudentService::listAllColleges()
{
    return collegeRepo.findAll();
}

std::vector<Class> StudentService::listAllClass()
{
    return classRepo.findAll();
}

std::vector<Major> StudentService::listAllMajors()
{
    return majorRepo.findAll();
}

std::optional<StudentDetail> StudentService::getStudentDetail(int personId)
{
    /*
    StudentDetail
    {
        int personId = 0;
        std::string name;
        std::string nameType;
        std::string gender;
        int genderConfidence;
        std::string residence;
        int residenceConfidence;
        std::string className;
        std::string majorName;
        std::string collegeName;
    }
    */

    auto student = studentRepo.findByPersonId(personId);
    if (!student)
        return std::nullopt;

    auto person = personRepo.findById(personId);
    if (!person)
        return std::nullopt;

    auto classInfo = classRepo.findById(student->getClassId());
    if (!classInfo)
        return std::nullopt;

    auto major = majorRepo.findById(classInfo->getMajorId());
    if (!major)
        return std::nullopt;

    auto college = collegeRepo.findById(major->getCollegeId());
    if (!college)
        return std::nullopt;

    StudentDetail result = {
        personId,
        person->getName(),
        person->getNameType(),
        person->getGender(),
        person->getGenderConfidence(),
        person->getResidence(),
        person->getResidenceConfidence(),
        classInfo->getClassNumber(),
        major->getName(),
        college->getName()};

    return result;
}

std::vector<StudentSummary> StudentService::searchStudents(const std::string &keyword)
{

    std::vector<StudentSummary> result;

    if (keyword.empty())
    {
        return listAllStudents();
    }

    auto allStudents = listAllStudents();

    for (const auto &student : allStudents)
    {
        if (student.name.find(keyword) != std::string::npos ||
            student.nameTpye.find(keyword) != std::string::npos ||
            student.gender.find(keyword) != std::string::npos ||
            student.className.find(keyword) != std::string::npos ||
            student.majorName.find(keyword) != std::string::npos ||
            student.collegeName.find(keyword) != std::string::npos ||
            student.residence.find(keyword) != std::string::npos)
        {
            result.push_back(student);
        }
    }

    return result;
}

std::vector<StudentSummary> StudentService::findUncertainStudents(
    const std::string &field,
    int confidence)
{
    std::vector<StudentSummary> result;

    auto allStudents = listAllStudents();

    for (const auto &student : allStudents)
    {
        bool genderUncertain = false;
        bool residenceUncertain = false;

        auto isUncertain = [confidence](
                               const std::string &value,
                               int actualConfidence)
        {
            if (confidence == -1)
            {
                return value.empty() || actualConfidence < 2;
            }

            if (value.empty())
            {
                return confidence == 0;
            }

            return actualConfidence == confidence;
        };

        if (field == "all" || field == "gender")
        {
            genderUncertain = isUncertain(
                student.gender,
                student.genderConfidence);
        }

        if (field == "all" || field == "residence")
        {
            residenceUncertain = isUncertain(
                student.residence,
                student.residenceConfidence);
        }

        if (genderUncertain || residenceUncertain)
        {
            result.push_back(student);
        }
    }

    return result;
}

bool StudentService::addStudent(const StudentDraft &draft)
{
    auto college = collegeRepo.findOrCreateByName(draft.collegeName);
    if (!college)
        return false;

    auto major = majorRepo.findOrCreateByName(draft.majorName, college->getId());
    if (!major)
        return false;

    auto classInfo = classRepo.findOrCreateByNumber(draft.className, major->getId());
    if (!classInfo)
        return false;

    Person person(
        draft.name,
        draft.nameType,
        draft.gender,
        draft.genderConfidence,
        draft.residence,
        draft.residenceConfidence);

    if (!personRepo.save(person))
        return false;

    Student student(person.getId(), classInfo->getId());
    return studentRepo.save(student);
}

bool StudentService::updateStudent(int personId, const StudentDraft &draft)
{
    auto student = studentRepo.findByPersonId(personId);
    if (!student)
        return false;

    auto college = collegeRepo.findOrCreateByName(draft.collegeName);
    if (!college)
        return false;

    auto major = majorRepo.findOrCreateByName(draft.majorName, college->getId());
    if (!major)
        return false;

    auto classInfo = classRepo.findOrCreateByNumber(draft.className, major->getId());
    if (!classInfo)
        return false;

    Person person(
        personId,
        draft.name,
        draft.nameType,
        draft.gender,
        draft.genderConfidence,
        draft.residence,
        draft.residenceConfidence);

    if (!personRepo.update(person))
        return false;

    if (student->getClassId() != classInfo->getId())
    {
        return studentRepo.updateClass(personId, classInfo->getId());
    }

    return true;
}

bool StudentService::deleteStudent(int personId)
{
    auto student = studentRepo.findByPersonId(personId);
    if (!student)
        return false;

    db.beginTransaction();

    if (!studentRepo.removeByPersonId(personId))
    {
        db.rollback();
        return false;
    }

    if (!personRepo.removeById(personId))
    {
        db.rollback();
        return false;
    }

    db.commit();
    return true;
}