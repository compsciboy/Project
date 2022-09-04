

class Disjoint_Set(object):

    '''
    An implementation of the disjoint set structure

    It is a collection of sets (S0 ... SN) which share no elements and can have a number of operations performed between them

    Each set will have some "respresentative" which is a string which can be used to identify the whole set.
    ''' 

    def __init__(self):

        '''
        This function is called any time a "Disjoint_Set" object is created, it sets up all the necessary parts and
        initializes their values
        '''

        # self.sets is a 'dictionary' which will associate a given number to the correct set
        # Example use would be self.sets['3'] should return the set with 3 as its representative 

        self.sets = {}

        # self.representatives is a set obejct that holds all representatives used in the disjoint set object

        self.representatives = set()

    def make_set(self, x):

        '''
        This function must take a single element and make a new set, then add that set to our self.sets with a key,
        the key should be a string, i.e. self.sets[3] wouldnt work but self.sets['3'] would
        '''

        # Make a new set 
        a = set([x])

        # Add the new set to self.sets
        self.sets.update({x : a})

        # Add the new key to self.representatives
        self.representatives.add(x)

        pass

    def Union(self, x, y):

        '''
        This function will take two representatives (as integers) and will create a new set that is the
        union of the two sets represented by them. 

        This new set will be added to self.sets with whichever key you choose (must be an element of the new set) and
        the two sets respresented by x and y will be removed from self.sets
        '''

        # Make the new unioned set
        a = self.sets[str(x)].union(self.sets[str(y)])

        # Add the new set to self.sets, then removed the old ones

        self.sets[str(x)] = a
        del self.sets[str(y)]


        # Add the new key to self.representatives, and remove the old ones
        self.representatives.remove(str(y))

        pass

    def Find_set(self, key):

        '''
        This method simply returns the set with the corresponding representative
        passed in as an integer 'key'

        '''

        key_set = self.sets[str(key)]

        return key_set

    def __len__(self):

        '''
        This is an override of the len function
        '''

        return len(self.representatives)

