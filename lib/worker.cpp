#include "worker.h"

Worker::Worker()
{
	first_name = "";
	last_name = "";
	email = "";
	zip_code = "";
	skills = List<std::string>();
	co_workers = List<Worker*>();
	company = NULL;
}

Worker::Worker(std::string _first_name, std::string _last_name, std::string _email)
{
	first_name = _first_name;
	last_name = _last_name;
	email = _email;
	zip_code = "";
	skills = List<std::string>();
	co_workers = List<Worker*>();
	company = NULL;
}

Worker::~Worker()
{
	return;
}

void Worker::add_skill(std::string skill)
{
	skills.addlast(skill);
}

void Worker::add_co_worker(Worker& co_worker)
{
	co_workers.addlast(&co_worker);
}

void Worker::set_zip_code(std::string _zip_code)
{
	zip_code = _zip_code;
}

void Worker::set_company(Company* _company)
{
	company = _company;
}

bool Worker::employed() const
{
	return company != NULL;
}

void Worker::remove_from_coll()
{
	auto it = co_workers.begin();
	while(it != co_workers.end())
	{
		(*it)->co_workers.remove(this);
		it++;
	}
}

bool operator==(Worker& l, Worker& r)
{
	return l.first_name == r.first_name && l.last_name == r.last_name;
}

bool operator!=(Worker& l, Worker& r)
{
	return !(l==r);
}

std::ostream& operator<<(std::ostream& os, const Worker& w)
{
	os << w.first_name << " " << w.last_name << " (email: " << w.email;
	if (w.employed()) os << ", Travaille chez " << w.company->name;
	os << ")";
	// os << ", Compétences: ";
	// auto it = w.skills->first;
	// while (it != w.skills->last)
	// {
	// 	os << it->data << ", ";
	// 	it = it->next;
	// }
	// os << it->data;
	return os;
}

Worker* srch_wrk_list(List<Worker*>& workers, std::string first_name, std::string last_name)
{
	Worker* w = NULL;
	auto it = workers.begin();

	while (it != workers.end() && w == NULL)
	{
		if ((*it)->first_name == first_name && (*it)->last_name == last_name) w = (*it);
		it++;
	}
	return w;
}

bool wrk_exist(List<Worker*>& workers, std::string first_name, std::string last_name)
{
	return srch_wrk_list(workers, first_name, last_name) != NULL;
}

List<Worker*>* company_employees(List<Worker*>& workers, Company& c)
{
	List<Worker*>* l = new List<Worker*>();
	auto it = workers.begin();
	while (it != workers.end())
	{
		if (*(*it)->company == c) l->addlast(*it);
		it++;
	}
	return l;
}

void load_wrk()
{
	return;
}
