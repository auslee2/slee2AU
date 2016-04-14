__author__ = 'sLee'
import scto


def test_scto():
    """
    nosestest to see the possible relationship between each class of number.
    :return:
    """
    bound = 10

    for x in range(1, bound):
        square = scto.square_g(x)
        cubic = scto.cubic_g(x)
        tetrahedral = scto.tetrahedral_g(x)
        octahedral = scto.oct_g(x)
        twonlessonetetra = 2*scto.tetrahedral_g(x-1)
        nlesstwotetra = scto.tetrahedral_g(x-2)
        #snum = scto.tetrahedral_g(x-1)

        #c = x
        '''while c != 0:
            snum = snum + (c*c)
            c = c -1'''
        #new_oct = 2*snum + square
        # print(snum)
        #########################################################################
        # remove '#' for each testing case
        # scto table:
        new_oct = cubic -scto.oct_g(x-1)+square
        print('square: {0}\t cubic: {1}\t tetrahedral: {2}\t octahedral: {3}\t newOctahedral: {4}\n'  \
              .format(square, cubic, tetrahedral, octahedral, new_oct))
        #########################################################################
        # check if On == Tn +2T(n-1) +Tn-2
        # assert octahedral == tetrahedral + twonlessonetetra +nlesstwotetra
        # print('octahedral(n): {0}\ttetrahedral(n): {1}\t2*tetrahedral(n-1): {2}\ttetrahedral(2n-1): {3}\n' \
        #       .format(octahedral, tetrahedral, twonlessonetetra, nlesstwotetra))
        ##########################################################################
        ## check if n^3 == On + 2T(n-1)
        #assert cubic == octahedral + twonlessonetetra
        #print('cubic(n): {0}\toctahedral(n): {1}\t2tetrahedral(n-1): {2}\n' \
        #      .format(cubic, octahedral, twonlessonetetra))
        #########################################################################