# https://github.com/fluentpython/example-code/blob/master/14-it-generator/sentence_iter.py

# Duck type
# we do not care about the actual class of the object
# but as long as it behave like a duck it should be a duck
# Monkey patching
# change a class or module at run time without touching the sourcd code
# protocl are dynamic
# e.g. random.shuffle does not care bout what type of argument it gets, it only
# needs the object to implement part of the mutable sequence protocol
# theo object methond can also be added at runtime



# --------------------------------------------------------------------
import collections
import random

Card = collections.namedtuple('Card', ['rank', 'suit'])

# inherite MutableSequence ,as to implements its interface(complulsory)
class FrenchDeck2(collections.MutableSequence):
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()

    def __init__(self):
        self._cards = [Card(rank, suit) for suit in self.suits
                                        for rank in self.ranks]

    def __len__(self):
        return len(self._cards)

    def __getitem__(self, position):
        return self._cards[position]

    # all need for shuffle
    def __setitem__(self, position, value):  # <1>
        self._cards[position] = value

    # requried by the MutableSequence abc
    def __delitem__(self, position):  # <2>
        del self._cards[position]

    # requried by the MutableSequence abc
    def insert(self, position, value):  # <3>
        self._cards.insert(position, value)

cards = FrenchDeck2()
# shuffle needs mutable sequece we have __getitem__
# and __setitem__ which makes shuffle works
random.shuffle(cards)
print(cards[:])
# --------------------------------------------------------------------

# BEGIN TOMBOLA_ABC

import abc

class Tombola(abc.ABC):  # <1>

    # abstract method that to be overriden by the subclass
    @abc.abstractmethod
    def load(self, iterable):  # <2>
        """Add items from an iterable."""

    @abc.abstractmethod
    def pick(self):  # <3>
        """Remove item at random, returning it.
        This method should raise `LookupError` when the instance is empty.
        """
    # concrete method is allowed as long as they only depend on the 
    # interface methods
    def loaded(self):  # <4>
        """Return `True` if there's at least 1 item, `False` otherwise."""
        return bool(self.inspect())  # <5>


    def inspect(self):
        """Return a sorted tuple with the items currently inside."""
        items = []
        while True:  # <6>
            try:
                items.append(self.pick())
            except LookupError:
                break
        self.load(items)  # <7>
        return tuple(sorted(items))


# END TOMBOLA_ABC

# BEGIN LOTTERY_BLOWER

import random

from tombola import Tombola


class LotteryBlower(Tombola):

    def __init__(self, iterable):
        self._balls = list(iterable)  # <1>

    def load(self, iterable):
        self._balls.extend(iterable)

    def pick(self):
        try:
            position = random.randrange(len(self._balls))  # <2>
        except ValueError:
            raise LookupError('pick from empty BingoCage')
        return self._balls.pop(position)  # <3>

    def loaded(self):  # <4>
        return bool(self._balls)

    def inspect(self):  # <5>
        return tuple(sorted(self._balls))


# END LOTTERY_BLOWER





