def compact_dict(dic, prev_key=''):
    out = []
    for key, val in dic.items():
        if not isinstance(val, dict):
            out.append((f'{prev_key}{key}', val))
        else:
            out.extend(compact_dict(dic[key], f'{prev_key}{key}.'))
    return out


example = {'b': 4,
           'c': {
               'd': {
                   'a': 3,
                   'r': 8,
                   't': 7},
               'e': 5}}

print(compact_dict(example))
