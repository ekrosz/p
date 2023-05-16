using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Ulstu_1
{
    internal class Program1
    {
        static void Main(string[] args)
        {
            // Инициализация и заполнение списка продуктов.
            var products = Enumerable.Range(0, 20).Select(i => new Product
            {
                Id = Guid.NewGuid(),
                Name = Guid.NewGuid().ToString(),
                Price = new Random().NextDouble() * new Random().Next(100, 1000),
                Components = new() { Guid.NewGuid().ToString(), Guid.NewGuid().ToString() }
            }).ToList();

            // Инициализация сериализатора с указанием типа, который мы сериализуем/десериализуем
            var serializer = new XmlSerializer(typeof(List<Product>));

            // Сериализация
            // получаем поток, куда будем записывать сериализованный объект. Сгенерированный искать в папке с проектом, папка bin/Debug/net5.0
            using (FileStream fs = new FileStream("persons.xml", FileMode.Create))
            {
                serializer.Serialize(fs, products);
            }

            // Десериализация
            using (FileStream fs = new FileStream("persons.xml", FileMode.OpenOrCreate))
            {
                var deserializedPersons = (List<Product>)serializer.Deserialize(fs);
                Console.WriteLine($"Price: {deserializedPersons.First().Price}");
            }
        }
    }

    /// <summary>
    /// Продукт.
    /// </summary>
    [XmlRoot]
    public class Product
    {
        [XmlAttribute("id" /*Если не указывать имя, то будет взято имя переменной*/ )] // данное поле будет находиться в атрибутах продукта. Свойственно указывать для идентификаторов.
        public Guid Id { get; set; }

        [XmlElement("name")] // данное поле будет элементом продукта. Свойственно указывать для обычных полей.
        public string Name { get; set; }

        [XmlElement("price")] // данное поле будет элементом продукта. Свойственно указывать для обычных полей.
        public double Price { get; set; }

        [XmlArray] // будет помечен как массив в элементе продуктов. Свойственно указывать для коллекций.
        public List<string> Components { get; set; }
    }
}
