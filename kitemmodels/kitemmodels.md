# KItemModels

## Abstract

KItemModels is a set of classes built for or on top of [Qt's model view system](http://qt-project.org/doc/qt-5/model-view-programming.html). It contains a collection
of additional proxy models and other utilities to help make complex tasks around models simpler. The following chapter will go through all of them one by one

## KBreadcrumbSelectionModel

The `KBreadcrumbSelectionModel` is a selection model that ensures that some or all parents of items in trees are selected when a given item is selected. `KBreadcrumbSelectionModel` 
makes creating breadcrumb navigation bar easy with this.

## KCheckableProxyModel

The `KCheckableProxyModel` adds checkable capability to an `QAbstractItemModel` without having to modify the model itself and implement the right parts of data, setData and flags methods. The checkable 
proxy model also works nicely together with the `KSelectionProxyModel` to show the items checked off.

## KDescendantsProxyModel

`KDescendantsProxyModel` flattens a tree model into a list with the possibility to still make it visually appear like a tree by indentation or by showing the parent's

## KLinkItemSelectionModel

`KLinkItemSelectionModel` makes it possible to share a selection between multiple views that has different proxy models in between the root model and the view

## KModelIndexProxyMapper

`KModelIndexProxyMapper` facilitates mapping between two different branches of proxy models on top of the same base root model.

## KRecursiveFilterProxyModel

Filtering a tree model where the child items are of interest, `QSortFilterProxyModel` is not the right thing. `QSortFilterProxyModel` does not look at children if a parent is filtered out.
`KRecursiveFilterProxyModel` goes through the tree and includes a item and all its parents.

## KSelectionProxyModel

`KSelectionProxyModel`  Convenience filtering model to just show the items that are included by a `QItemSelectionModel`



