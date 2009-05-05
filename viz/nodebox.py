import sys
sys.path.append('/Library/Python/2.5/site-packages')
import MySQLdb
import math, datetime, time
from pprint import pprint

try:
    graph = ximport("graph")
    coreimage = ximport("coreimage")
    colors = ximport("colors")
except ImportError:
    graph = ximport("__init__")
    reload(graph)
    coreimage = ximport("__init__")
    reload(coreimage)
    colors = ximport("__init__")
    reload(colors)

size(1280, 720)
frame = 0

rl = None
g = None

def setup():
    global frame
    frame += 1
    
    global rl
    rl = RenderNodeList()

    #### Different Rendering Methods
    
    '''render_loopy()
    this is trying to loop the cohorts together...
    '''
    
    render_random()
    ''' This uses randomness to make it not chug so much '''
    
    
    
    '''
    print g
    for obj in g:
    	  print obj
    print g.styles
    for obj in g.styles:
    	  print obj
    print g.styles.default
    for obj in g.styles.default:
    	  print obj
    '''

# bluetooth	
# bt = lightblue.finddevices()
# print bt
test = 'blah'
test = ''

speed(30)
def draw():
    global frame
    frame += 1

    
    # Background
    bg = colors.color(0.01, 0.03, 0.05, 0.4)
    clr = bg # colors.color(bg).darker(0.2)
    bgr = rect(0, 0, 1280, 720)                  
    colors.gradientfill(bgr, clr, clr.lighter(0.25))                      
    colors.shadow(dx=0, dy=0, blur=6, alpha=0.935, clr=bg)

    # Polling Information
    font('Helvetica', 10)
    text('Bluetooth device discovery polled once every 2 minutes', 0, 0)

    # Logo
    img = "blueball.png"
    canvas = coreimage.canvas(240, 60)
    logo = canvas.append(img)
    logo.scale(0.8)   
    glow = canvas.append("blueball.glow.png")
    op = (math.cos(frame*0.2) * 0.4) + 0.5
    glow.scale(0.8)
    glow.blend(op)
    canvas.draw(1000, 650)
    

    
    # Render Each set detected at a time as cohorts, age the lines
    # Grow Size based on how many times it's remained tehre
    # Color based on classtype
    # add particle glow (blue) - ring when first appears
    
    # If the graph layout is done,
    # show the shortest path between random nodes.
    path = []
    if g.done:
        if random() > 0.5:
            render_random()
        else:
            render_loopy()
        #id1 = choice(g.keys())
        #id2 = choice(g.keys())
        #path = g.shortest_path(id1, id2)
        '''
        node1 = g.add_node(random(10))
        if random() > 0.5:
            for i in range(choice((1, 4))):
                node2 = choice(g.nodes)
                g.add_edge(node1.id, node2.id, weight=random())
        '''
        pass
        
    # Draw the graph and display the shortest path.
    g.draw(highlight=path, traffic=4, weighted=True, directed=False)

    # Display it on screen by concatenating the strings.
    # text("%s: %s." % (test,test), 10, 48, width=WIDTH-20, fontsize=38, font="Helvetica-Bold", fill=1)
    # Polling Information
    
    # rect(0, 0, 1280, 720)


### Node Classes ###

class RenderNodeList:
    def __init__(self):
        self.conn = MySQLdb.connect(user='blueball', passwd='blueball', db='blueball', host='randomfoo.net')
        self.addq = []
        self.removeq = []
        
        # Initial Loadup
        self.getFullList()
        
        # Reader
    '''
    def __init__(self):
        try:
            self.conn = MySQLdb.connect(user='blueball', passwd='blueball', db='blueball', host='localhost')
            self.c = self.conn.cursor()
        except OperationalError:
            pass

    '''	  
    def getFullList(self):
        # self.addq
        sql = "SELECT devices.id AS id, devices.name AS name, major, minor, total_count, lastseen, scantime, sensor FROM history, devices WHERE devices.id = history.id ORDER BY scantime DESC, sensor LIMIT 100"
        self.addq += self.db_query(sql)
        
        # self.removeq
        # none
        # call _updateAge
        
        # addqueue
        # removequeue
        pass
    def getStats(self):
        sql = "SELECT COUNT(*) FROM devices"
        sql = "SELECT COUNT(*) FROM history"
        sql = "SELECT major, minor, COUNT(*) AS COUNT FROM devices GROUP BY minor ORDER BY COUNT DESC"
        
    def db_query(self, sql, t=None):                                                      
        cursor = self.conn.cursor(MySQLdb.cursors.DictCursor)                       
        cursor.execute(sql, t)                                                         
        result = cursor.fetchall()                                                  
        cursor.close()                                                              
        return result                                                               
                                                                                
    def db_insert(self, sql, t):                                                     
        cursor = self.conn.cursor(MySQLdb.cursors.DictCursor)                       
        result = cursor.execute(sql, t)                                                
        cursor.close()
        self.conn.commit()                                                          
        return result
        
### Rendering Functions

def render_loopy():    
    # Graph
    global g
    g = graph.create(iterations=200, distance=1.6, layout="spring")

    # Sensors
    nodeA = g.add_node('Front Entrance')
    nodeB = g.add_node('Side Entrance')
    nodeC = g.add_node('Main Room')

    # Add nodes with a random id,
    # connected to other random nodes.
    cohorts = []
    scantime = 0
    sensor = ''
    cohort = None
    for row in rl.addq:
    	   # Is it in the same cohort?
        if scantime != row['scantime'] or sensor != row['sensor']:
            if cohort:
                if sensor == 'a':
                    g.add_edge(cohort.id, nodeA.id, weight=0.2)
                elif sensor == 'b':
                    g.add_edge(cohort.id, nodeB.id, weight=0.2)
                elif sensor == 'c':
                    g.add_edge(cohort.id, nodeC.id, weight=0.2)       
            cohorts = []
            scantime = row['scantime']
            sensor = row['sensor']
            
        
        node = g.add_node(row['name'])
        
        # node properties
        # count
        # continuous count
        '''
        if['total_count']
        {'major': 'COMPUTER', 'name': 'Unnamed', 'scantime': 1210715959L, 'total_count': 2L, 'lastseen': 1210715959L, 'sensor': 'c', 'id': '00:0D:93:0E:E2:55', 'minor': 'LAPTOP'}
        
        '''        
        # Add Sensor edge to start
        if len(cohorts) == 0:
            if sensor == 'a':
                g.add_edge(node.id, nodeA.id, weight=0.5)
            elif sensor == 'b':
                g.add_edge(node.id, nodeB.id, weight=0.5)
            elif sensor == 'c':
                g.add_edge(node.id, nodeC.id, weight=0.5)
        # Add Cohort edges - one to each
        else:
            cohort = cohorts.pop()
            g.add_edge(node.id, cohort.id, weight=0.1)
        
        # TODO: if edge is there will strengthen?
        # 1 edge

        cohorts.append(node)
    	   
        # pprint(row)
        # major, minor, lastseen, scantime, sensor
        
        # flow
        
        '''
            for i in range(choice((1, 4))):
                node2 = choice(g.nodes)
                g.add_edge(node1.id, node2.id, weight=random())
        '''
    g.prune()
    # print g.styles.background
    g.styles.default.background = None
    g.styles.default.depth = None
    
    g.styles.apply()


def render_random():    
    # Graph
    global g
    g = graph.create(iterations=200, distance=2.4, layout="spring")

    # Sensors
    nodeA = g.add_node('Front Entrance')
    nodeB = g.add_node('Side Entrance')
    nodeC = g.add_node('Main Room')

    # Add nodes with a random id,
    # connected to other random nodes.
    cohorts = []
    scantime = 0
    sensor = ''
    cohort = None
    for row in rl.addq:
    	   # Is it in the same cohort?
        if scantime != row['scantime'] or sensor != row['sensor']:
            cohorts = []
            scantime = row['scantime']
            sensor = row['sensor']
                    
        node = g.add_node(row['name'])
        
        # node properties
        # count
        # continuous count
        '''
        if['total_count']
        {'major': 'COMPUTER', 'name': 'Unnamed', 'scantime': 1210715959L, 'total_count': 2L, 'lastseen': 1210715959L, 'sensor': 'c', 'id': '00:0D:93:0E:E2:55', 'minor': 'LAPTOP'}
        
        '''        
        # Add Sensor edge to start
        if random() > 0.5:
            if sensor == 'a':
                g.add_edge(node.id, nodeA.id, weight=0.5)
            elif sensor == 'b':
                g.add_edge(node.id, nodeB.id, weight=0.5)
            elif sensor == 'c':
                g.add_edge(node.id, nodeC.id, weight=0.5)

        # Add Cohort edges
        for cohort in cohorts:
            if random() > 0.8:
                g.add_edge(node.id, cohort.id, weight=0.1)
        
        # TODO: if edge is there will strengthen?
        # 1 edge

        cohorts.append(node)
    	   
        # pprint(row)
        
        
        '''
            for i in range(choice((1, 4))):
                node2 = choice(g.nodes)
                g.add_edge(node1.id, node2.id, weight=random())
        '''
    g.prune()
    # print g.styles.background
    g.styles.default.background = None
    g.styles.default.depth = None
    
    g.styles.apply()
