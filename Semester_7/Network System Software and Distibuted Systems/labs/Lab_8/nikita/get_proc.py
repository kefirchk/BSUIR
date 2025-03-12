import random
import numpy as np

def get_by_group(total_processes, num_groups):
    print(f"Proc: {total_processes}")
    print(f"Groups: {num_groups}")

    group_sizes = [random.randint(1, total_processes) for _ in range(num_groups)]

    while sum(group_sizes) != total_processes:
        group_sizes = [random.randint(1, total_processes) for _ in range(num_groups)]

    groups = []
    remaining_processes = list(range(total_processes))

    for size in group_sizes:
        if remaining_processes:
            selected = random.sample(remaining_processes, min(size, len(remaining_processes)))
            groups.append(selected)
            remaining_processes = [p for p in remaining_processes if p not in selected]

    print("Size of groups:", group_sizes)
    print("Groups:", groups)
    
    return groups