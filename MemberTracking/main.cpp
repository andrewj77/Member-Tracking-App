#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	ifstream file("config.txt");
	string repositoryType;
	getline(file, repositoryType);
	repositoryType = repositoryType.substr(13);
	string fileType;
	getline(file, fileType);
	fileType = fileType.substr(8);
	Validator validator;

	shared_ptr<Repository> repository;
	shared_ptr<Repository> fileRepository;
	if (repositoryType == "memory")
		repository = make_shared<MemoryRepository>();
	else if (repositoryType == "file")
		repository = make_shared<FileRepository>();

	if (fileType == "csv")
		fileRepository = make_shared<CsvRepository>();
	else if (fileType == "html")
		fileRepository = make_shared<HtmlRepository>();
	MembersTableModel* model = new MembersTableModel(fileRepository);
	SavedMembersWidget* table = new SavedMembersWidget(model);
	Service service(validator, repository, fileRepository);
	service.addObserver(table);
	GUI gui{ service, table};
    gui.show();
    return app.exec();
}
