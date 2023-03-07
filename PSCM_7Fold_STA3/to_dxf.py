import logging
from AutomateSuperPackage.AutomateSuperModule import DatabaseClass
import yaml
import ezdxf
from ezdxf import units




config_file_path = "config.yaml"
with open(config_file_path, 'r') as f:
    YAML = yaml.safe_load(f)
ACCES = DatabaseClass().AccesDatabase
ACCES.multipleCursors([YAML["DATABASE"]]),

def getResult(Query):
    ACCES.MultipleWriteQuery(Query,[0])
    return ACCES.MultipleResultFromQuery([0])
doc = ezdxf.new('R2018') # create a new DXF drawing in R2010 fromat 
msp = doc.modelspace() # add new entities to the modelspace
factor = 1e6


data = getResult(f"SELECT x,y,onDevice,type FROM inserts WHERE Type LIKE '%mil%'")
for rows in data:
    hole_size_in_mils = int(rows[3].split("mil")[0])
    hole_size_in_mm = hole_size_in_mils*0.0254
    print(hole_size_in_mm)
    msp.add_circle(((rows[0]/factor),(rows[1]/factor)), hole_size_in_mm/2*1e-3, dxfattribs={'layer': 'PROBES','color': 3, "lineweight": -3})
    #msp.add_text(f"{rows[2]}", dxfattribs={'height': 500, 'layer': 'PinName','color': 2}).set_pos((int(rows[0]),int(rows[1])), align='MIDDLE_CENTER')
    msp.add_text(f"{rows[0]}{rows[1]}", dxfattribs={'height': 1e-4, 'layer': 'PROBES-Cordinates','color': 3}).set_pos(((rows[0]/factor),(rows[1]/factor)), align='MIDDLE_CENTER')

data = getResult(f"SELECT x,y,onDevice FROM inserts WHERE Type = 'Pin'")
for rows in data:
    msp.add_circle(((rows[0]/factor),(rows[1]/factor)), 1e-3, dxfattribs={'layer': 'pins','color': 2})
    #msp.add_text(f"{rows[2]}", dxfattribs={'height': 500, 'layer': 'PinName','color': 2}).set_pos((int(rows[0]),int(rows[1])), align='MIDDLE_CENTER')
    msp.add_text(f"{rows[0]}{rows[1]}", dxfattribs={'height': 1e-4, 'layer': 'pins-Cordinates','color': 2}).set_pos(((rows[0]/factor),(rows[1]/factor)), align='MIDDLE_CENTER')


data = getResult(f"SELECT x,y,onDevice FROM inserts WHERE type = 'Tooling'")
for rows in data:
    msp.add_circle(((rows[0]/factor),(rows[1]/factor)), 1e-3, dxfattribs={'layer': 'Tooling-pins','color': 4})
    #msp.add_text(f"{rows[2]}", dxfattribs={'height': 500, 'layer': 'PinName','color': 2}).set_pos((int(rows[0]),int(rows[1])), align='MIDDLE_CENTER')
    msp.add_text(f"{rows[0]}{rows[1]}", dxfattribs={'height': 1e-4, 'layer': 'Tooling-Cordinates','color': 4}).set_pos(((rows[0]/factor),(rows[1]/factor)), align='MIDDLE_CENTER')

num_of_outlines = int(getResult("SELECT TOP 1 global_outline_number FROM fixture_OUTLINE ORDER BY global_outline_number DESC")[0][0])
for i in range(num_of_outlines-2):
    data = getResult(f"SELECT x,y FROM fixture_OUTLINE WHERE global_outline_number = {i+1}")
    print(data)
    placement = getResult("SELECT PLACEMENT_x,PLACEMENT_y FROM fixture_OUTLINE WHERE TYPE_OF_OUTLINE = 'PLACEMENT'")[i]
    print(f"PLACEMENT: {placement}")
    placement_x = placement[0]/factor
    placement_y = placement[1]/factor
    msp.add_circle((placement_x,placement_y), 4e-3, dxfattribs={'layer': 'PLACEMENT-origins','color': 6})

    for row_index in range(len(data)-1):
        print(row_index)
        msp.add_line((data[row_index][0]/factor,data[row_index][1]/factor),(data[row_index+1][0]/factor,data[row_index+1][1]/factor), dxfattribs={'layer': 'OUTLINE','color': 5})

doc.saveas('test_line.dxf') 


import sys
import matplotlib.pyplot as plt
from ezdxf import recover
from ezdxf.addons.drawing import RenderContext, Frontend
from ezdxf.addons.drawing.matplotlib import MatplotlibBackend

logging.getLogger("ezdxf").setLevel(logging.ERROR)
logging.getLogger("matplotlib").setLevel(logging.CRITICAL)
logging.getLogger("MatplotlibBackend").setLevel(logging.CRITICAL)
# Safe loading procedure (requires ezdxf v0.14):
try:
    doc, auditor = recover.readfile('test_line.dxf')
except IOError:
    print(f'Not a DXF file or a generic I/O error.')
    sys.exit(1)
except ezdxf.DXFStructureError:
    print(f'Invalid or corrupted DXF file.')
    sys.exit(2)

# The auditor.errors attribute stores severe errors,
# which may raise exceptions when rendering.
if not auditor.has_errors:
    fig = plt.figure()
    ax = fig.add_axes([0, 0, 1, 1])
    ctx = RenderContext(doc)
    out = MatplotlibBackend(ax)
    Frontend(ctx, out).draw_layout(doc.modelspace(), finalize=True)
    fig.savefig('test_line.png', dpi=300)
    #print(doc)