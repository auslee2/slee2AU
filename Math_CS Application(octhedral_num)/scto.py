__author__ = 'sLee'
'''This program is attempting to create a generating and
visualizing relationship between different number
(such as square, cubic, and octahedral numbers)'''
square = ''
cubic = ''
tetrahedral = ''
octahedral = ''


def square_g(n):
    """
    This is square number generator
    :param n:
    :return:
    """
    n_sqr = n*n
    return n_sqr


def cubic_g(n):
    """
    This is cubic number generator
    :param n:
    :return:
    """
    n_cubic = n*n*n
    return n_cubic


def tetrahedral_g(n):
    """
    This is tetrahedra number
    :param n:
    :return:
    """
    n_tetra = n*(n+1)*(n+2)/6
    return n_tetra


def oct_g(n):
    """This is octahedral number generator"""
    n_oct = n*(2*n*n+1)/3
    return n_oct

def tri_g(n):
    """triangular number generator"""
    n_tri = n(n+1)/2
    return n_tri






