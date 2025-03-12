import random
from argparse import ArgumentParser

from mpi4py import MPI


def _generate_groups(group_count, process_count):
    # Начальное распределение: по одному элементу в каждую группу
    initial_distribution = [1] * group_count
    remaining_elements = process_count - group_count

    # Распределяем оставшиеся элементы случайным образом по группам
    for _ in range(remaining_elements):
        initial_distribution[random.randint(0, group_count - 1)] += 1

    # Генерируем список элементов и распределяем их по группам
    elements = list(range(process_count))
    groups = []
    start = 0

    # Разбиваем список элементов по сгенерированным размерам
    for group_size in initial_distribution:
        groups.append(elements[start:start + group_size])
        start += group_size

    print(groups)

    return groups


def create_groups(comm, process_count):
    parser = ArgumentParser(description="groups")
    parser.add_argument("-g", "--groups", type=int, required=True, help="groups count")
    args = parser.parse_args()

    processes = {}
    groups = []

    # Только процесс с рангом 0 создает группы
    if comm.rank == 0:
        groups = _generate_groups(args.groups, process_count)

    # Распространение групп от процесса с рангом 0 ко всем остальным
    groups = comm.bcast(groups, root=0)

    # Обновляем словарь dist для всех процессов
    for gid, ranks in enumerate(groups):
        sgroup = MPI.Group.Incl(comm.Get_group(), ranks)
        processes.update({rank: (gid, sgroup) for rank in ranks})

    return processes, groups