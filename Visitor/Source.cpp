#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class CPU;
class HDD;
class RAM;
class GPU;

class IVisitor abstract {
public:
    virtual void VisitProcessor(CPU* proc) abstract;
    virtual void VisitHdd(HDD* hdd) abstract;
    virtual void VisitRAM(RAM* ram) abstract;
    virtual void VisitGPU(GPU* gpu) abstract;
};

class AbstractDevice abstract {
    string Producer;
public:
    virtual void Accept(IVisitor* visitor) abstract;
    string GetProducer(){
        return Producer;
    }
    void SetProducer(string Producer) {
        this->Producer = Producer;
    }
};

class CPU : public AbstractDevice {
    string Frequency;
    string CoreCount;
public:
    string GetFrequency(){
        return  Frequency;
    }
    void SetFrequency(string Frequency) {
        this->Frequency = Frequency;
    }
    string GetCoreCount(){
        return CoreCount;
    }
    void SetCoreCount(string CoreCount) {
        this->CoreCount = CoreCount;
    }
    void Accept(IVisitor* visitor) override {
        visitor->VisitProcessor(this);
    }
};

class HDD : public AbstractDevice {
    string Volume;
    string Type;
public:
    string GetVolume() {
        return Volume;
    }
    void SetVolume(string Volume) {
        this->Volume = Volume;
    }
    string GetType() {
        return Type;
    }
    void SetType(string Type) {
        this->Type = Type;
    }
    void Accept(IVisitor* visitor) override {
        visitor->VisitHdd(this);
    }
};

class RAM : public AbstractDevice {
    string Capacity;
public:
    string GetCapacity() {
        return Capacity;
    }
    void SetCapacity(string Capacity) {
        this->Capacity = Capacity;
    }
    void Accept(IVisitor* visitor) override {
        visitor->VisitRAM(this);
    }
};

class GPU : public AbstractDevice {
    string Model;
public:
    string GetModel() {
        return Model;
    }
    void SetModel(string Model) {
        this->Model = Model;
    }
    void Accept(IVisitor* visitor) override {
        visitor->VisitGPU(this);
    }
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor {
public:
    void VisitProcessor(CPU* proc) override {
        ofstream out("Processor.html", ios::binary | ios::trunc | ios::out);
        string result = "<html><head></head><body>";
        result += "<table><tr><td>Property<td><td>Value</td></tr>";
        result += "<tr><td>Producer<td><td>" + proc->GetProducer() + "</td></tr>";
        result += "<tr><td>Frequency<td><td>" + proc->GetFrequency() + "</td></tr>";
        result += "<tr><td>CoreCount<td><td>" + proc->GetCoreCount() + "</td></tr></table>";
        result += "</body></html>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitHdd(HDD* hdd) override {
        ofstream out("Hdd.html", ios::binary | ios::trunc | ios::out);
        string result = "<html><head></head><body>";
        result += "<table><tr><td>Property<td><td>Value</td></tr>";
        result += "<tr><td>Producer<td><td>" + hdd->GetProducer() + "</td></tr>";
        result += "<tr><td>Type<td><td>" + hdd->GetType() + "</td></tr>";
        result += "<tr><td>Volume<td><td>" + hdd->GetVolume() + "</td></tr></table>";
        result += "</body></html>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitRAM(RAM* ram) override {
        ofstream out("RAM.html", ios::binary | ios::trunc | ios::out);
        string result = "<html><head></head><body>";
        result += "<table><tr><td>Property<td><td>Value</td></tr>";
        result += "<tr><td>Producer<td><td>" + ram->GetProducer() + "</td></tr>";
        result += "<tr><td>Capacity<td><td>" + ram->GetCapacity() + "</td></tr></table>";
        result += "</body></html>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitGPU(GPU* gpu) override {
        ofstream out("GPU.html", ios::binary | ios::trunc | ios::out);
        string result = "<html><head></head><body>";
        result += "<table><tr><td>Property<td><td>Value</td></tr>";
        result += "<tr><td>Producer<td><td>" + gpu->GetProducer() + "</td></tr>";
        result += "<tr><td>Model<td><td>" + gpu->GetModel() + "</td></tr></table>";
        result += "</body></html>";
        out.write(result.c_str(), result.size());
        out.close();
    }
};

// сериализатор в XML
class XmlVisitor : public IVisitor {
public:
    void VisitProcessor(CPU* proc) override {
        ofstream out("Processor.xml", ios::binary | ios::trunc | ios::out);
        string result = "<?xml version='1.0' encoding='UTF-8'?>";
        result += "<Processor><Producer>" + proc->GetProducer() + "</Producer>" +
            "<Frequency>" + proc->GetFrequency() + "</Frequency>" +
            "<CoreCount>" + proc->GetCoreCount() + "</CoreCount></Processor>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitHdd(HDD* hdd) override {
        ofstream out("Hdd.xml", ios::binary | ios::trunc | ios::out);
        string result = "<?xml version='1.0' encoding='UTF-8'?>";
        result += "<HDD><Producer>" + hdd->GetProducer() + "</Producer>" +
            "<Type>" + hdd->GetType() + "</Type>" +
            "<Volume>" + hdd->GetVolume() + "</Volume></HDD>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitRAM(RAM* ram) override {
        ofstream out("RAM.xml", ios::binary | ios::trunc | ios::out);
        string result = "<?xml version='1.0' encoding='UTF-8'?>";
        result += "<RAM><Producer>" + ram->GetProducer() + "</Producer>" +
            "<Capacity>" + ram->GetCapacity() + "</Capacity></RAM>";
        out.write(result.c_str(), result.size());
        out.close();
    }
    void VisitGPU(GPU* gpu) override {
        ofstream out("GPU.xml", ios::binary | ios::trunc | ios::out);
        string result = "<?xml version='1.0' encoding='UTF-8'?>";
        result += "<GPU><Producer>" + gpu->GetProducer() + "</Producer>" +
            "<Model>" + gpu->GetModel() + "</Model></GPU>";
        out.write(result.c_str(), result.size());
        out.close();
    }
};

class TextVisitor : public IVisitor {
public:
    void VisitProcessor(CPU* proc) override {
        ofstream out("Processor.txt", ios::trunc);
        out << "Processor\n";
        out << "Producer: " << proc->GetProducer() << "\n";
        out << "Frequency: " << proc->GetFrequency() << "\n";
        out << "CoreCount: " << proc->GetCoreCount() << "\n";
        out.close();
    }

    void VisitHdd(HDD* hdd) override {
        ofstream out("Hdd.txt", ios::trunc);
        out << "HDD\n";
        out << "Producer: " << hdd->GetProducer() << "\n";
        out << "Type: " << hdd->GetType() << "\n";
        out << "Volume: " << hdd->GetVolume() << "\n";
        out.close();
    }

    void VisitRAM(RAM* ram) override {
        ofstream out("RAM.txt", ios::trunc);
        out << "RAM\n";
        out << "Producer: " << ram->GetProducer() << "\n";
        out << "Capacity: " << ram->GetCapacity() << "\n";
        out.close();
    }

    void VisitGPU(GPU* gpu) override {
        ofstream out("GPU.txt", ios::trunc);
        out << "GPU\n";
        out << "Producer: " << gpu->GetProducer() << "\n";
        out << "Model: " << gpu->GetModel() << "\n";
        out.close();
    }
};

class ConsoleVisitor : public IVisitor {
public:
    void VisitProcessor(CPU* proc) override {
        cout << "Processor\n";
        cout << "Producer: " << proc->GetProducer() << "\n";
        cout << "Frequency: " << proc->GetFrequency() << "\n";
        cout << "CoreCount: " << proc->GetCoreCount() << "\n";
    }

    void VisitHdd(HDD* hdd) override {
        cout << "HDD\n";
        cout << "Producer: " << hdd->GetProducer() << "\n";
        cout << "Type: " << hdd->GetType() << "\n";
        cout << "Volume: " << hdd->GetVolume() << "\n";
    }

    void VisitRAM(RAM* ram) override {
        cout << "RAM\n";
        cout << "Producer: " << ram->GetProducer() << "\n";
        cout << "Capacity: " << ram->GetCapacity() << "\n";
    }

    void VisitGPU(GPU* gpu) override {
        cout << "GPU\n";
        cout << "Producer: " << gpu->GetProducer() << "\n";
        cout << "Model: " << gpu->GetModel() << "\n";
    }
};

class PC {
    vector<AbstractDevice*> devices;
public:
    void Add(AbstractDevice* d) {
        devices.push_back(d);
    }
    void Remove(AbstractDevice* d) {
        auto iter = find(devices.begin(), devices.end(), d);
        if (iter != devices.end())
            devices.erase(iter);
    }
    void Accept(IVisitor* visitor) {
        for (AbstractDevice* d : devices)
            d->Accept(visitor);
    }
};

int main() {
    PC* pc = new PC();
    CPU* p = new CPU;
    p->SetProducer("AMD Ryzen 10 8240HS");
    p->SetFrequency("4.2 Ghz");
    p->SetCoreCount("16");
    pc->Add(p);

    HDD* hdd = new HDD;
    hdd->SetProducer("Samsung 12345 PRO Super");
    hdd->SetType("NVME SSD");
    hdd->SetVolume("2TB");
    pc->Add(hdd);

    RAM* ram = new RAM;
    ram->SetProducer("Kingston");
    ram->SetCapacity("64GB");
    pc->Add(ram);

    GPU* gpu = new GPU;
    gpu->SetProducer("NVIDIA");
    gpu->SetModel("RTX 4080 TI");
    pc->Add(gpu);

    HtmlVisitor* html = new HtmlVisitor;
    pc->Accept(html);
    XmlVisitor* xml = new XmlVisitor;
    pc->Accept(xml);
    TextVisitor* text = new TextVisitor;
    pc->Accept(text);
    ConsoleVisitor* console = new ConsoleVisitor;
    pc->Accept(console);

    delete html;
    delete xml;
    delete text;
    delete console;
    delete gpu;
    delete ram;
    delete hdd;
    delete p;
    delete pc;

    system("pause");
    return 0;
}