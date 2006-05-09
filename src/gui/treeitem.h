#ifndef __TREEITEM_H__
#define __TREEITEM_H__

#include <iproperty.h>
#include <qlistview.h>
#include "treeitemabstract.h"
class QString;

namespace gui {

using namespace pdfobjects;

class TreeWindow;

class TreeItemObserver;//internal class (observer)

class TreeItem : public TreeItemAbstract {
public:
 static TreeItem* create(TreeData *_data,QListView *parent,boost::shared_ptr<IProperty> pdfObj,const QString &name=QString::null,QListViewItem *after=NULL,const QString &nameId=QString::null);
 static TreeItem* create(TreeData *_data,QListViewItem *parent,boost::shared_ptr<IProperty> pdfObj,const QString &name=QString::null,QListViewItem *after=NULL,const QString &nameId=QString::null);
 TreeItem* parent();
 virtual ~TreeItem();
 boost::shared_ptr<IProperty> getObject();
 void setParent(TreeItem *parent);
 virtual void insertItem(QListViewItem *newChild);
 void unSelect();
 //From TreeItemAbstract interface
 virtual void reloadSelf();
 virtual QSCObject* getQSObject();
 virtual void remove();
protected:
 TreeItem(const QString &nameId,TreeData *_data,QListView *parent,boost::shared_ptr<IProperty> pdfObj,const QString &name=QString::null,QListViewItem *after=NULL);
 TreeItem(const QString &nameId,TreeData *_data,QListViewItem *parent,boost::shared_ptr<IProperty> pdfObj,const QString &name=QString::null,QListViewItem *after=NULL);
 void initObserver();
 void uninitObserver();
protected:
 void init(boost::shared_ptr<IProperty> pdfObj,const QString &name);
 /** CObject stored in this TreeItem */
 boost::shared_ptr<IProperty> obj;
 /** Type of stored object */
 PropertyType typ;
 /** Parent of this window if it is TreeItem. NULL if no parent or parent is not a TreeItem */
 TreeItem *_parent;
 /** Observer registered for this item */
 boost::shared_ptr<TreeItemObserver> observer;
};

} // namespace gui

#endif
