using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;

namespace Ulstu_1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // Инициализация и заполнение списка продуктов.
            var products = Enumerable.Range(0, 20).Select(i => new Product
            {
                Id = Guid.NewGuid(),
                Name = Guid.NewGuid().ToString(),
                Price = new Random().NextDouble() * new Random().Next(100, 1000),
                Type = Enum.GetValues<Type>().ToArray()[new Random().Next(0, 1)]
            });

            var components = Enumerable.Range(0, 20).Select(i => new Component
            {
                Id = Guid.NewGuid(),
                Name = Guid.NewGuid().ToString(),
                ProductId = products.ElementAt(new Random().Next(0, products.Count() - 1)).Id
            });

            // Выборка.
            // Получение всех продуктов, которые в наименовании имеют подстроку "4" и их цена больше 100.
            var list1 = products.Where(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет первый попавшийся продукт, если он будет удовлетворять указанному условию, иначе вернет NULL.
            var element1 = products.FirstOrDefault(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет первый попавшийся продукт, если он будет удовлетворять указанному условию, иначе вернет ошибку.
            var element2 = products.First(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет последний попавшийся продукт, если он будет удовлетворять указанному условию, иначе вернет NULL.
            var element3 = products.LastOrDefault(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет последний попавшийся продукт, если он будет удовлетворять указанному условию, иначе вернет ошибку.
            var element4 = products.Last(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет первый попавшийся продукт, если он будет удовлетворять указанному условию и будет единственный, который удовлетворяет условию, иначе вернет NULL в случае не находа или ошибку в случае находа нескольких элементов.
            var element5 = products.SingleOrDefault(product => product.Name.Contains("4") && product.Price > 100);
            // Вернет первый попавшийся продукт, если он будет удовлетворять указанному условию и будет единственный, который удовлетворяет условию, иначе вернет ошибку в случае не находа или ошибку в случае находа нескольких элементов.
            var element6 = products.Single(product => product.Name.Contains("4") && product.Price > 100);

            // Группировка по типу продукта.
            var list2 = list1.GroupBy(product => product.Type);

            // Агрегатные функции.
            var sum = products.Sum(product => product.Price); // сумма
            var avg = products.Average(product => product.Price); // среднее
            var min = products.Min(product => product.Price); // минимальное
            var max = products.Max(product => product.Price); // максимальное
            var count = products.Count(product => product.Type == Type.New); // количество продуктов, удовлетворяющее условию. Можно вызвать просто Count(), чтоб узнать количество элементов в коллекции без условия

            // Преобразование в кастомную модель (SELECT) с группировкой (GROUP BY)
            var list3 = products.GroupBy(product => product.Type)
                .Select(product => new ProductsByType
                {
                    Type = product.Key,
                    Products = product.ToList()
                });

            // Указанное значение может являться только вложенная коллекция. Возвращает коллекцию продуктов, объединяя все подколлекции в основной коллекции.
            var list4 = list3.SelectMany(productsByType => productsByType.Products);

            // Преобразование в разные коллекции: лист, массив, словарь
            var enumerableToList = products.ToList();
            var enumerableToArray = products.ToArray();
            var enumerableToDictionary = products.ToDictionary(product => product.Name, product => product.Price); // Key = Product.Name, Value = Product.Price 

            // Соединение через Джойны
            var joinedData = products.Join(components, product => product.Id, component => component.ProductId, (product, component) => new ProductComponent
            {
                ProductName = product.Name,
                ComponentName = component.Name,
                ProductPrice = product.Price,
                ProductType = product.Type
            });

            // Метод Distinct для выборки уникальных значений.
            var distinctTypes = products.Select(product => product.Type).Distinct();
            
            // Вернет True, если все продукты будут удовлетворять указанному условию.
            var all = products.All(product => product.Price > 0);
            // Вернет True, если хотя бы один продукт будет удовлетворять указанному условию.
            var any = products.Any(product => product.Price > 100);

            // Разность последовательностей. Будет возвращены те продукты, которые не входят в коллекцию list1.
            var except = products.Except(list1);
            // Пересечение последовательностей. Будет возвращены те продукты, которые входят в коллекцию list1.
            var intersect = products.Intersect(list1);
            // Объединение последовательностей. Будет возвращена объеденная коллекция products с list1.
            var union = products.Union(list1);

            // OrderBy - сортировка по возрастанию по указанному полю. ThenBy - дополнительная сортировка по возрастанию по указанному полю (всегда идет после OrderBy и OrderByDescending).
            var orderBy = products.OrderBy(product => product.Name)
                .ThenBy(product => product.Price);

            // OrderBy - сортировка по убыванию по указанному полю. ThenByDescending - дополнительная сортировка по убыванию по указанному полю (всегда идет после OrderBy и OrderByDescending).
            var orderByDescending = products.OrderByDescending(product => product.Name)
                .ThenByDescending(product => product.Price);

            // Skip - количество элементов, которые пропускаются из последовательности. Take - количество элементов, которое берется из последовательности.
            var skipTake = products.Skip(3).Take(2);
        }
    }

    /// <summary>
    /// Продукт.
    /// </summary>
    public class Product
    {
        public Guid Id { get; set; }

        public string Name { get; set; }

        public double Price { get; set; }

        public Type Type { get; set; }
    }

    public class Component
    {
        public Guid Id { get; set; }

        public Guid ProductId { get; set; }

        public string Name { get; set; }
    }

    public class ProductComponent
    {
        public string ProductName { get; set; }

        public string ComponentName { get; set; }

        public double ProductPrice { get; set; }

        public Type ProductType { get; set; }
    }

    /// <summary>
    /// Тип продукта: новый или Б/У
    /// </summary>
    public enum Type
    {
        New = 1,

        Used = 2
    }

    public class ProductsByType
    {
        public Type Type { get; set; }

        public List<Product> Products { get; set; }
    }
}
