#include <Python.h>
#include "sorts.h"

/*
   This file defines a python module using the CPython C-API.
*/


/* Python extension overhead*/
struct module_state {
    PyObject *error;
};

static char bubble_docstring[] = "C bubble sort implementation";
static char naive_merge_docstring[] = "Naive C merge sort implementation";
static char naive_mt_docstring[] = "Multi-threaded C merge sort implementation";

static PyObject *_sorts_naive_merge(PyObject *self, PyObject *args);
static PyObject *_sorts_mt_merge(PyObject *self, PyObject *args);
static PyObject *_sorts_bubble(PyObject *self, PyObject *args);

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

static PyObject* error_out(PyObject *m){
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "ERRORS EVERYWHERE");
    return NULL;
}

static PyMethodDef _sorts_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_VARARGS, NULL},
    {"bubble", _sorts_bubble, METH_VARARGS, bubble_docstring},
    {"naive_merge", _sorts_naive_merge, METH_VARARGS, naive_merge_docstring},
    {"mt_merge", _sorts_mt_merge, METH_VARARGS, naive_mt_docstring},
    {NULL, NULL, 0, NULL}
};

static int _sorts_traverse(PyObject *m, visitproc visit, void *arg){
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int _sorts_clear(PyObject *m){
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "_sorts",
    NULL,
    sizeof(struct module_state),
    _sorts_methods,
    NULL,
    _sorts_traverse,
    _sorts_clear,
    NULL
};

PyMODINIT_FUNC PyInit__sorts(){
    PyObject *module = PyModule_Create(&moduledef);
    if (module == NULL)
        return NULL;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("_sorts.Errlr", NULL, NULL);
    if (st->error == NULL){
        Py_DECREF(module);
        return NULL;
    }
    return module;
}


/* Module function definitions.*/
static PyObject *_sorts_naive_merge(PyObject *self, PyObject *args){
    /* Wrapper for the function in sorts.c that defines 
        a naive (single threaded) merge sort.
    */
    int ii;
    PyObject *input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj))
        return NULL;
    PyObject *seq = PySequence_Fast(input_obj, "Expected sequence object");
    if (!seq)
        return NULL;
    Py_ssize_t len = PySequence_Length(seq);
    int array[len];
    for(ii = 0; ii < len; ii++){
        PyObject *elem = PySequence_Fast_GET_ITEM(seq, ii);
        /* TODO: Allow ints using PyLong_Check.*/
        if (!PyFloat_Check(elem)){
            char err[40];
            sprintf(err, "Expected float in position %d", ii);
            PyErr_SetString(PyExc_TypeError, err);
            return NULL;
        } else {
            double a = PyFloat_AsDouble(elem);
            array[ii] = a;
        }
    }
    sort(array, (int)len);
    PyObject* result = PyList_New(len);
    PyObject* number;
    for(ii = 0; ii < len; ii++){
        number = PyFloat_FromDouble(array[ii]);
        if(number == NULL)
            return NULL;
        PyList_SetItem(result, ii, number);
    }
    return result;
}

static PyObject *_sorts_mt_merge(PyObject *self, PyObject *args){
    /* Wrapper for the function in sorts.c that defines 
        a multi-threaded merge sort.
    */
    int ii;
    PyObject *input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj))
        return NULL;
    PyObject *seq = PySequence_Fast(input_obj, "Expected sequence object");
    if (!seq)
        return NULL;
    Py_ssize_t len = PySequence_Length(seq);
    int array[len];
    for(ii = 0; ii < len; ii++){
        PyObject *elem = PySequence_Fast_GET_ITEM(seq, ii);
        /* TODO: Allow ints using PyLong_Check.*/
        if (!PyFloat_Check(elem)){
            char err[40];
            sprintf(err, "Expected float in position %d", ii);
            PyErr_SetString(PyExc_TypeError, err);
            return NULL;
        } else {
            double a = PyFloat_AsDouble(elem);
            array[ii] = a;
        }
    }
    mt_sort(array, (int)len);
    PyObject* result = PyList_New(len);
    PyObject* number;
    for(ii = 0; ii < len; ii++){
        number = PyFloat_FromDouble(array[ii]);
        if(number == NULL)
            return NULL;
        PyList_SetItem(result, ii, number);
    }
    return result;
}

static PyObject *_sorts_bubble(PyObject *self, PyObject *args){
    /* Wrapper for the function in sorts.c that defines 
        a bubble sort.
    */
    int ii;
    PyObject *input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj))
        return NULL;
    PyObject *seq = PySequence_Fast(input_obj, "Expected sequence object");
    if (!seq)
        return NULL;
    Py_ssize_t len = PySequence_Length(seq);
    int array[len];
    for(ii = 0; ii < len; ii++){
        PyObject *elem = PySequence_Fast_GET_ITEM(seq, ii);
        /* TODO: Allow ints using PyLong_Check.*/
        if (!PyFloat_Check(elem)){
            char err[40];
            sprintf(err, "Expected float in position %d", ii);
            PyErr_SetString(PyExc_TypeError, err);
            return NULL;
        } else {
            double a = PyFloat_AsDouble(elem);
            array[ii] = a;
        }
    }
    bubble(array, (int)len);
    PyObject* result = PyList_New(len);
    PyObject* number;
    for(ii = 0; ii < len; ii++){
        number = PyFloat_FromDouble(array[ii]);
        if(number == NULL)
            return NULL;
        PyList_SetItem(result, ii, number);
    }
    return result;
}
