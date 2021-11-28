from automata.tm.dtm import DTM

dtm = DTM(
        states={'q0', 'q1', 'q2', 'q3', 'q4', 'q5', 'q6', 'q7'},
        input_symbols={'1', 'M'},
        tape_symbols={'1', 'M', 'X', 'B'},
        transitions={
            'q0': {
                '1': ('q1', 'X', 'R'),
                'M': ('q5', 'M', 'R')
            },
            'q1': {
                '1': ('q1', '1', 'R'),
                'M': ('q2', 'M', 'R')
            },
            'q2': {
                'X': ('q2', 'X', 'R'),
                '1': ('q3', 'X', 'L')
            },
            'q3': {
                'X': ('q3', 'X', 'L'),
                'M': ('q4', 'M', 'L')
            },
            'q4': {
                '1': ('q4', '1', 'L'),
                'X': ('q0', 'X', 'R')
            },
            'q5': {
                'X': ('q5', 'X', 'R'),
                '1': ('q6', '1', 'L'),
            },
            'q6': {
                'X': ('q7', 'B', 'R')
            }
        },
        initial_state='q0',
        blank_symbol='B',
        final_states={'q7'}
)
