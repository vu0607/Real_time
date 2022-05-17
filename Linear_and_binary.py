# Datastructures 1 :
test = {
    'input' : {
        'card' : [1,2,3,4],
        'query': 7
    },
    'output' : 3
}
def locate_position1(cards,query):
    position = 0
    while True:
        if len(cards) == 0:
            return -2
        if cards[position] == query:
            return position
        position +=1 
        if position > len(cards):
            return -1
#print(locate_position([],3))
# Datastructures 2 :
def locate_position2(cards,query):
    start, end = 0 , len(cards) - 1
    while start <= end:
        mid = (start + end) // 2
        mid_number = cards[mid]
        if mid_number == query:
            while cards[mid-1] == query:
                mid = mid-1
            return mid
        elif mid_number < query:
            start = mid + 1
        elif mid_number > query:
            end = mid - 1
    return -1
#print(locate_position2([],6))

