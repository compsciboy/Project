import random
import math

BOT_NAME = "Omega"


class RandomAgent:
    """Agent that picks a random available move.  You should be able to beat it."""

    def get_move(self, state, depth=None):
        return random.choice(state.successors())


class HumanAgent:
    """Prompts user to supply a valid move."""

    def get_move(self, state, depth=None):
        move__state = dict(state.successors())
        prompt = "Kindly enter your move {}: ".format(sorted(move__state.keys()))
        move = None
        while move not in move__state:
            try:
                move = int(input(prompt))
            except ValueError:
                continue
        return move, move__state[move]


class MinimaxAgent:
    """Artificially intelligent agent that uses minimax to optimally select the best move."""

    def get_move(self, state, depth=None):
        """Select the best available move, based on minimax value."""
        nextp = state.next_player()
        best_util = -math.inf if nextp == 1 else math.inf
        best_move = None
        best_state = None

        for move, state in state.successors():
            util = self.minimax(state, depth)
            if ((nextp == 1) and (util > best_util)) or ((nextp == -1) and (util < best_util)):
                best_util, best_move, best_state = util, move, state
        return best_move, best_state

    def minimax(self, state, depth):
        """Determine the minimax utility value of the given state.

        Args:
            state: a connect383.GameState object representing the current board
            depth: for this agent, the depth argument should be ignored!

        Returns: the exact minimax utility value of the state
        """

        if state.is_full():
            return state.score()

        nextp = state.next_player()
        u = -math.inf if nextp == 1 else math.inf

        for m, s in state.successors():
            if nextp == 1:
                u = max(u, self.minimax(s, depth))
            else:
                u = min(u, self.minimax(s, depth))
        return u


class HeuristicAgent(MinimaxAgent):
    """Artificially intelligent agent that uses depth-limited minimax to select the best move."""

    def minimax(self, state, depth):
        return self.minimax_depth(state, depth)

    def minimax_depth(self, state, depth):
        """Determine the heuristically estimated minimax utility value of the given state.

        Args:
            state: a connect383.GameState object representing the current board
            depth: the maximum depth of the game tree that minimax should traverse before
                estimating the utility using the evaluation() function.  If depth is 0, no
                traversal is performed, and minimax returns the results of a call to evaluation().
                If depth is None, the entire game tree is traversed.

        Returns: the minimax utility value of the state
        """
        if depth is None:
            return MinimaxAgent.minimax(self, state, None)
        if state.is_full():
            return state.score()
        elif depth == 0:
            return self.evaluation(state)

        nextp = state.next_player()
        u = -math.inf if nextp == 1 else math.inf

        for m, s in state.successors():
            if nextp == 1:
                u = max(u, self.minimax_depth(s, depth - 1))
            else:
                u = min(u, self.minimax_depth(s, depth - 1))
        return u

    def evaluation(self, state):
        """Estimate the utility value of the game state based on features.

        N.B.: This method must run in O(1) time!

        Args:
            state: a connect383.GameState object representing the current board

        Returns: a heusristic estimate of the utility value of the state
        """
        p1 = 0
        p2 = 0
        for run in state.get_all_rows() + state.get_all_cols() + state.get_all_diags():
            if (len(run) > 2) and (0 in run and (1 in run or -1 in run)):
                a = heuristic(run)
                p1 += a[1]
                p2 += a[-1]
        return p1 - p2


class PruneAgent(HeuristicAgent):
    """Smarter computer agent that uses minimax with alpha-beta pruning to select the best move."""

    def minimax(self, state, depth):
        return self.minimax_prune(state, depth)

    def minimax_prune(self, state, depth):
        """Determine the minimax utility value the given state using alpha-beta pruning.

        The value should be equal to the one determined by ComputerAgent.minimax(), but the
        algorithm should do less work.  You can check this by inspecting the class variables
        GameState.p1_state_count and GameState.p2_state_count, which keep track of how many
        GameState objects were created over time.

        N.B.: When exploring the game tree and expanding nodes, you must consider the child nodes
        in the order that they are returned by GameState.successors().  That is, you cannot prune
        the state reached by moving to column 4 before you've explored the state reached by a move
        to to column 1.

        Args: see ComputerDepthLimitAgent.minimax() above

        Returns: the minimax utility value of the state
        """

        if depth is None:
            return minimax_alpha_beta(state, depth, -math.inf, math.inf)

        else:
            return minimax_alpha_beta_depth(state, depth, -math.inf, math.inf)


def minimax_alpha_beta_depth(state, depth, alpha, beta):
    if state.is_full():
        return state.score()
    if depth == 0:
        return HeuristicAgent.evaluation(state, state)

    nextp = state.next_player()
    u = -math.inf if nextp == 1 else math.inf

    for m, s in state.successors():
        if nextp == 1:
            u = max(u, minimax_alpha_beta_depth(s, depth - 1, alpha, beta))
            alpha = max(alpha, u)
            if beta <= alpha:
                break
        else:
            u = min(u, minimax_alpha_beta_depth(s, depth - 1, alpha, beta))
            beta = min(beta, u)
            if beta <= alpha:
                break
    return u


def minimax_alpha_beta(state, depth, alpha, beta):
    if state.is_full():
        return state.score()

    nextp = state.next_player()
    u = -math.inf if nextp == 1 else math.inf

    for m, s in state.successors():
        if nextp == 1:
            u = max(u, minimax_alpha_beta(s, depth, alpha, beta))
            alpha = max(alpha, u)
            if beta <= alpha:
                break
        else:
            u = min(u, minimax_alpha_beta(s, depth, alpha, beta))
            beta = min(beta, u)
            if beta <= alpha:
                break
    return u


def heuristic(array):
    prev = array[0]
    count = 1
    out = {1: 0, -1: 0}
    for i in range(1, len(array)):
        if prev == 0:
            if array[i] != 0:
                count = count + 1
            prev = array[i]
            continue
        if array[i] == 0:
            count += 1
            if i < len(array) - 1 and prev == array[i + 1]:
                continue
        if array[i] == prev:
            count += 1
        else:
            if count > 2:
                out[prev] += count ** 2
            prev = array[i]
            count = 1
    if prev != 0 and count > 2:
        out[prev] += count ** 2
    return out
