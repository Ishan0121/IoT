import re

files = [
    'exp03.html', 'exp04.html', 'exp05.html', 
    'exp06.html', 'exp07.html', 'exp08.html', 
    'exp09.html', 'exp10.html'
]

for fname in files:
    try:
        with open(f"/home/phantom/Documents/Codes/Aetheris/IoT/Learn/web/{fname}", 'r') as f:
            html = f.read()
        
        parts = html.split('<section class="section">')
        preamble = parts[0]
        sections = parts[1:]
        
        sim_indices = []
        adv_index = -1
        
        for i, sec in enumerate(sections):
            if "Simulator" in sec or "Simulation" in sec or "Web Dashboard Preview" in sec:
                # We need to ensure we don't accidentally grab a simple solution or other section that has the word simulator in the text.
                # Check if it's in the h2 title
                if '<h2 class="section-title">' in sec:
                    title = sec.split('<h2 class="section-title">')[1].split('</h2>')[0]
                    if "Simulator" in title or "Simulation" in title or "Preview" in title:
                        sim_indices.append(i)
            if "Advanced Solution" in sec and '<h2 class="section-title">' in sec:
                title = sec.split('<h2 class="section-title">')[1].split('</h2>')[0]
                if "Advanced Solution" in title:
                    adv_index = i
                    
        if not sim_indices or adv_index == -1:
            print(f"Skipping {fname} - missing expected sections.")
            continue
            
        sim_sections = [sections[i] for i in sim_indices]
        
        for i in reversed(sim_indices):
            sections.pop(i)
            
        adv_index = -1
        for i, sec in enumerate(sections):
            if "Advanced Solution" in sec and '<h2 class="section-title">' in sec:
                adv_index = i
                break
                
        for sec in reversed(sim_sections):
            sections.insert(adv_index, sec)
            
        new_html = preamble + "".join(['<section class="section">' + s for s in sections])
        
        with open(f"/home/phantom/Documents/Codes/Aetheris/IoT/Learn/web/{fname}", 'w') as f:
            f.write(new_html)
            
        print(f"Processed {fname} successfully.")
    except Exception as e:
        print(f"Error processing {fname}: {e}")

