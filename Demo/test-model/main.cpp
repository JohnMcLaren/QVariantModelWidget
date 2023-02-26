#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include "../../qvariantmodel.h"
//#include "../../qvarianttreewidget.h"
//#include "../../qvarianttablewidget.h"
//------------------------------------
int main(int argc, char *argv[])
{
QCoreApplication a(argc, argv);
//QJsonObject jobj =QJsonDocument::fromJson("{  \"links\": {    \"self\": \"http://example.com/articles\",    \"next\": \"http://example.com/articles?page[offset]=2\",    \"last\": \"http://example.com/articles?page[offset]=10\"  },  \"data\": [{    \"type\": \"articles\",    \"id\": \"1\",    \"attributes\": {      \"title\": \"JSON:API paints my bikeshed!\"    },    \"relationships\": {      \"author\": {        \"links\": {          \"self\": \"http://example.com/articles/1/relationships/author\",          \"related\": \"http://example.com/articles/1/author\"        },        \"data\": { \"type\": \"people\", \"id\": \"9\" }      },      \"comments\": {        \"links\": {          \"self\": \"http://example.com/articles/1/relationships/comments\",          \"related\": \"http://example.com/articles/1/comments\"        },        \"data\": [          { \"type\": \"comments\", \"id\": \"5\" },          { \"type\": \"comments\", \"id\": \"12\" }        ]      }    },    \"links\": {      \"self\": \"http://example.com/articles/1\"    }  }],  \"included\": [{    \"type\": \"people\",    \"id\": \"9\",    \"attributes\": {      \"firstName\": \"Dan\",      \"lastName\": \"Gebhardt\",      \"twitter\": \"dgeb\"    },    \"links\": {      \"self\": \"http://example.com/people/9\"    }  }, {    \"type\": \"comments\",    \"id\": \"5\",    \"attributes\": {      \"body\": \"First!\"    },    \"relationships\": {      \"author\": {        \"data\": { \"type\": \"people\", \"id\": \"2\" }      }    },    \"links\": {      \"self\": \"http://example.com/comments/5\"    }  }, {    \"type\": \"comments\",    \"id\": \"12\",    \"attributes\": {      \"body\": \"I like XML better\"    },    \"relationships\": {      \"author\": {        \"data\": { \"type\": \"people\", \"id\": \"9\" }      }    },    \"links\": {      \"self\": \"http://example.com/comments/12\"    }  }]}").object();
QJsonObject jobj =QJsonDocument::fromJson("{\"isbn\": \"\",  \"editor\": {\"lastname\": \"Smith\", \"firstname\": \"Jane\"}, \"title\": \"The Ultimate Database Study Guide\", \"category\": [\"Non-Fiction\", \"Technology\"]}").object();
QVM model;

	model.setData(QVMI {}, jobj.toVariantMap()); // init model by 'jobj' JsonObject

	qDebug() << QJsonDocument::fromVariant(model.data({})).toJson(QJsonDocument::Indented).data(); // print data of model

	model.setData({"isbn"}, "123-456-222"); // set new value for 'isbn' key
	model.insertData({"author"}, QVariantMap {{"lastname", "Doe"}, {"firstname", "Jane"}}); // insert new key 'author' as Map
	model.removeData({"editor"}); // remove existing key 'editor' of model
	qDebug() << "---------------------------------";
	//qDebug() << QJsonDocument::fromVariant(model.data({})).toJson(QJsonDocument::Indented).data();
	qDebug() << QJsonDocument(model.data({}).toJsonObject()).toJson(QJsonDocument::Indented).data(); // print result after modifications
//return a.exec();
}
