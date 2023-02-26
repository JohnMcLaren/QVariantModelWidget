#include "main.h"
#include <QApplication>

Window *win;
QHBoxLayout *lay;
QTimer tmr;
//---------------------------------------
QVariantList new_row2 ={rand(), rand(), rand(), rand()}; // create new row of values
int main(int argc, char *argv[])
{
QApplication app(argc, argv);

	win = new Window(600, 400);
	lay = new QHBoxLayout(win);
	lay->addWidget(&win->treeTest);
	lay->addWidget(&win->tableTest);

// The main data container 'map'. The completed JSON object will be copied into this container.
// [IMPORTANT] It should exist as long as the data is used by the Tree/Table widgets (if they are not using the inner container).
QVariant DataSource;
//Test JSON-map. We will add a test table here later.
//QJsonObject jbig =QJsonDocument::fromJson("{  \"links\": {    \"self\": \"http://example.com/articles\",    \"next\": \"http://example.com/articles?page[offset]=2\",    \"last\": \"http://example.com/articles?page[offset]=10\"  },  \"data\": [{    \"type\": \"articles\",    \"id\": \"1\",    \"attributes\": {      \"title\": \"JSON:API paints my bikeshed!\"    },    \"relationships\": {      \"author\": {        \"links\": {          \"self\": \"http://example.com/articles/1/relationships/author\",          \"related\": \"http://example.com/articles/1/author\"        },        \"data\": { \"type\": \"people\", \"id\": \"9\" }      },      \"comments\": {        \"links\": {          \"self\": \"http://example.com/articles/1/relationships/comments\",          \"related\": \"http://example.com/articles/1/comments\"        },        \"data\": [          { \"type\": \"comments\", \"id\": \"5\" },          { \"type\": \"comments\", \"id\": \"12\" }        ]      }    },    \"links\": {      \"self\": \"http://example.com/articles/1\"    }  }],  \"included\": [{    \"type\": \"people\",    \"id\": \"9\",    \"attributes\": {      \"firstName\": \"Dan\",      \"lastName\": \"Gebhardt\",      \"twitter\": \"dgeb\"    },    \"links\": {      \"self\": \"http://example.com/people/9\"    }  }, {    \"type\": \"comments\",    \"id\": \"5\",    \"attributes\": {      \"body\": \"First!\"    },    \"relationships\": {      \"author\": {        \"data\": { \"type\": \"people\", \"id\": \"2\" }      }    },    \"links\": {      \"self\": \"http://example.com/comments/5\"    }  }, {    \"type\": \"comments\",    \"id\": \"12\",    \"attributes\": {      \"body\": \"I like XML better\"    },    \"relationships\": {      \"author\": {        \"data\": { \"type\": \"people\", \"id\": \"9\" }      }    },    \"links\": {      \"self\": \"http://example.com/comments/12\"    }  }]}").object();
QJsonObject jbig =QJsonDocument::fromJson("{\"links\": [\"link1\", \"link2\"]}").object();
// Test table
QVariant varTable {QVariantList { // rows
					QVariantList {"(top-left)", "(0,1)", "(0,2)", "(0,3)", "(top-right)"},		// columns of row 0
					QVariantList {"(1,0)", "(0,1)", "(1,2)", "(1,3)", "(1,4)"},					// columns of row 1
					QVariantList {"(bottom-left)", "(2,1)", "(2,2)", "(2,3)", "(bottom-right)"}  // columns of row 2
					}};
	jbig["test-table"] =varTable.toJsonValue(); // add test-table to JSON object
	DataSource =jbig.toVariantMap(); // copy temp JSON-object to QVariant container
//*
	// Tree
	win->treeTest.setHeaders({"Key", "Value", "Type"}); // Headers (optional)
	win->treeTest.setDataSource(DataSource); // set reference to data root
	win->treeTest.setReadOnly(false);
	// Table
	//win->tableTest.setHeaders({"column0", "column1", "column2", "column3"}); // Headers (optional)
	win->tableTest.setDataSource(DataSource); // set reference to data root (same as a Tree)
	win->tableTest.setRootView({"test-table"}); // set RootView for table in main tree by key {'test-table'}.
	win->tableTest.updateColumns(5);
	win->tableTest.setReadOnly(false);

	win->tableTest.connectToChanges(&win->treeTest); // Enable mutual notification of data change events (tableTest <-> treeTest).
//*/
bool state =0;

	// Change data by timer
	app.connect(&tmr, &QTimer::timeout, [&]() {

		QVariantList rand_list ={111, 111, 111, QVariant::fromValue(QList<int> {rand(), rand(), rand()})};
		QVariantList rand_list2 ={222, 222, 222, QVariant::fromValue(QList<int> {rand(), rand(), rand()})};
		//QVariantList new_row2 ={rand(), rand(), rand(), QVariant::fromValue(rand_list)}; // create new row of values
		QVariantList new_row ={1, 1, 1, QVariant::fromValue(rand_list), QVariant::fromValue(rand_list)};
		QVariantList new_row2 ={2, 2, QVariant::fromValue(rand_list2), QVariant::fromValue(rand_list2), 2};

//		static_cast<QUIntHash *>(reinterpret_cast<QVariantList &>(llv)[9].data())[0][333] =rand();
//		static_cast<QUIntHash *>(reinterpret_cast<QVariantList &>(llv)[9].data())[0][999] =rand();

//			win->tableTest.setData({"test-table", 1}, QVariant::fromValue(new_row)); // set new values of row 1
//			win->treeTest.setData({"test-table", 1, 3}, QVariant::fromValue(new_row));

			win->tableTest.insertData({"test-table", 1}, QVariant::fromValue(new_row));
//			win->treeTest.insertData({"test-table", 1}, QVariant::fromValue(new_row));

//			if(state ^=1)
//				win->treeTest.setData({"test-table", 1}, QVariant::fromValue(rand_list));
//			else
//				win->treeTest.setData({"test-table", 1}, QVariant::fromValue(new_row2));

//			if(state ^=1)
//				win->treeTest.insertData({"test-table", 2}, QVariant::fromValue(new_row));
//			else
//				win->treeTest.removeData({"test-table", 2});

//			if(state ^=1)
//				win->tableTest.insertData({"test-table", 2}, QVariant::fromValue(new_row));
//			else
//				win->tableTest.removeData({"test-table", 2});
		});

	tmr.start(2000);

	// ready ..
	win->show();

return(app.exec());
}
