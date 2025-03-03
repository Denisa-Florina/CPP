#include "ListaNotificare.h"
#include "validator.h"
#include <assert.h>


void ListaNOT::empty_list() noexcept {
	ListaNot.clear();
    notify();
}


void ListaNOT::add_apartament(const Locatar& l) {
	if (search_apartament(l.get_apartament()) == false)
	{
		ListaNot.push_back(l);
        notify();
	}
	else
		throw ListaException("Apartament deja in lista!");
}


void ListaNOT::sterge(string apartament) {
    int index = 0;
    bool gasit = false;
    for (auto& locatar : ListaNot) {
        if (locatar.get_apartament() == apartament) {
            gasit = true;
            break;
        }
        index++;
    }

    if (gasit == true) {
        ListaNot.erase(ListaNot.begin() + index);
        notify();
        return;
    }
    else {
        throw ListaException("Nu exista locatar cu apartament: " + apartament);
    }
}


void ListaNOT::generate_apartamente(int nr_apt, const vector<Locatar>& memory) {
    empty_list();
    auto to_contract = memory;
    shuffle(to_contract.begin(), to_contract.end(), std::default_random_engine(static_cast<unsigned int>(time(0))));
    while (nr_apt && !to_contract.empty())
    {
        add_apartament(to_contract.back());
        to_contract.pop_back();
        nr_apt--;
    }
    notify();
}

void ListaNOT::export_list(const string& name_file) {
    string filename = name_file;
    auto pos = filename.find_last_of(".");
    if (pos < filename.size())
    {
        auto file_extension = name_file.substr(pos);
        if (file_extension != ".html")
            filename = filename + ".html";
    }
    else
    {
        filename += ".html";
    }


    std::ofstream fout(filename);
    fout << "<html>\n"
        "<body>\n"
        "<head>\n"
        "    <h3 style=\" font-family: 'Caviar Dreams',serif; color:mediumpurple; \">Lista notificari</h3>\n"
        "    </head>\n"
        "<style>\n"
        "    p {\n"
        "        color: #D7BDE2 ;\n"
        "        background-color: #A9CCE3 ;\n"
        "        border: 1px solid black; }\n"
        "    table,th,td{\n"
        "        border: 1px solid black;\n"
        "    }\n"
        "    th{\n"
        "        color: darkviolet;\n"
        "    }\n"
        "    body{\n"
        "        background-color: #CACFD2;\n"
        "    }\n"
        "</style>\n";
    fout << "<table>\n"
        "\n"
        "        <th>Apartament</th>\n"
        "        <th>Nume proprietar</th>\n"
        "        <th>Suprafata</th>\n"
        "        <th>Tip</th>";
    for (const Locatar& sbj : ListaNot)
    {
        fout << "<tr>\n";
        fout << "<th>" << sbj.get_apartament() << "</th>\n"
            << "<th>" << sbj.get_nume_proprietar() << "</th>\n"
            << "<th>" << sbj.get_suprafata() << "</th>\n"
            << "<th>\n" << sbj.get_tip() << "</th>\n"
            << "</tr>\n";


    }
    fout << "</table>\n"
        "\n"
        "\n"
        "</body>\n"
        "</html>";

}

const vector<Locatar>& ListaNOT::get_List() {
	return ListaNot;

}
int ListaNOT::search_apartament(const string& apartament) {

	for (auto& locatar : ListaNot) {
		if (locatar.get_apartament() == apartament) {
			return true;
		}
	}

	return false;
}

void test_adauga() {
    ListaNOT lst;
    lst.add_apartament({ "A", "B", 523, "C" });
    lst.add_apartament({ "B", "B", 523, "C" });
    try
    {
        lst.add_apartament({ "B", "B", 523, "C" });
        assert(false);
    }
    catch (ListaException& e)
    {
        assert(e.getMessage()!="");
    }
    vector<Locatar> list = lst.get_List();
    assert(list.size() == 2);
}

void test_sterge() {
    ListaNOT lst;
    lst.add_apartament({ "A", "B", 523, "C" });
    lst.add_apartament({ "B", "B", 523, "C" });
    lst.empty_list();
    vector<Locatar> list = lst.get_List();
    assert(list.size() == 0);

}

void test_generate() {
    ListaNOT lst;
    ListaNOT lst2;
    lst.add_apartament({ "A", "B", 523, "C" });
    lst.add_apartament({ "B", "B", 523, "C" });
    lst.add_apartament({ "C", "B", 523, "C" });
    lst.add_apartament({ "D", "B", 523, "C" });
    lst2.generate_apartamente(2, lst.get_List());
    vector<Locatar> list = lst2.get_List();
    assert(list.size() == 2);
}

void test_export() {
    ListaNOT lst;
    lst.add_apartament({ "A", "B", 523, "C" });
    lst.add_apartament({ "B", "B", 523, "C" });
    lst.export_list("test.html");
}

void test_export2() {
    ListaNOT lst;
    lst.add_apartament({ "A", "B", 523, "C" });
    lst.add_apartament({ "B", "B", 523, "C" });
    lst.export_list("test2");
    lst.add_apartament({ "C", "B", 523, "C" });
    lst.export_list("test3.");
}
